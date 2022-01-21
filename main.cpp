#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <OpenXLSX.hpp>

using namespace std;
using namespace OpenXLSX;

struct Equipment {
    int id;
    string name;
    bool mode; // true stands for unlimited number of objects, false otherwise
};

struct Subproduct {
    int id;
    string name;
    unordered_map<int, pair<int, int>> equipmentDurations; // map from equipment_id to <duration, switch time>
    map<pair<int, int>, int> movementTimes; // map from from_equipment_id, to_equipment_id> to duration
};

struct Suborder {
    int id;
    string name;
    int subproductId;
    vector<int> incomingSuborders;
    vector<int> outcomingSuborders;
};

struct Order {
    int id;
    string name;
    int quantity;
    int price;
    vector<int> finalSuborders;
};

struct Operation {
    enum Type {
        MANUFACTURING,
        READJUSTMENT,
    };
    Type type;
    int suborderId;
    int equipmentId;
    int startTime;
    int finishTime;
};

vector<Equipment> equipments;
unordered_map<string, int> equipmentIds;

vector<Subproduct> subproducts;
unordered_map<string, int> subproductIds;

vector<Suborder> suborders;
unordered_map<string, int> suborderIds;

vector<Order> orders;
unordered_map<string, int> orderIds;

vector<Operation> operations;

void readEquipments(const XLWorksheet& xls) {
    int rowIt = 0;
    for (const auto& row : xls.rows()) {
        rowIt++;
        if (rowIt == 1)
            continue;
        std::vector<XLCellValue> values = row.values();
        int id = rowIt - 2;
        string name = values[1];
        string modeStr = values[2];
        if (name.empty())
            break;
        bool mode = (modeStr == "mode_1");
        Equipment equipment{.id = id, .name = name, .mode = mode};
        equipments.push_back(equipment);
        equipmentIds[name] = id;
    }
}

void readSubproducts(const XLWorksheet& xls) {
    int rowIt = 0;
    for (const auto& row : xls.rows()) {
        rowIt++;
        if (rowIt == 1)
            continue;
        std::vector<XLCellValue> values = row.values();
        string name = values[1];
        if (name.empty())
            break;
        int id = -1;
        if (!subproductIds.count(name)) {
            id = subproducts.size();
            Subproduct subproduct{.id = id, .name = name};
            subproducts.push_back(subproduct);
            subproductIds[name] = id;
        } else {
            id = subproductIds[name];
        }

        string equipmentName = values[2];
        assert(equipmentIds.count(equipmentName));
        int equipmentId = equipmentIds[equipmentName];
        int duration = values[3];
        subproducts[id].equipmentDurations[equipmentId].first = duration;
    }
}

void readSwitchTimes(const XLWorksheet& xls) {
    int rowIt = 0;
    for (const auto& row : xls.rows()) {
        rowIt++;
        if (rowIt == 1)
            continue;
        std::vector<XLCellValue> values = row.values();
        string name = values[2];
        if (name.empty())
            break;
        assert(subproductIds.count(name));
        int id = subproductIds[name];

        string equipmentName = values[1];
        if (!equipmentIds.count(equipmentName)) {
            continue;
        }
        int equipmentId = equipmentIds[equipmentName];
        assert(!equipments[equipmentId].mode);

        if (subproducts[id].equipmentDurations.count(equipmentId)) {
            int duration = 0;
            try {
                duration = values[3];
            } catch (exception e) {
                double durationDouble = values[3];
                duration = int(ceil(durationDouble) + 0.01);
            }
            subproducts[id].equipmentDurations[equipmentId].second = duration;
        }
    }
}

void readSuborders(const XLWorksheet& xls) {
    int rowIt = 0;
    for (const auto& row : xls.rows()) {
        rowIt++;
        if (rowIt == 1)
            continue;
        std::vector<XLCellValue> values = row.values();
        string name = values[2];
        if (name.empty())
            break;

        string subproductName = values[3];
        assert(subproductIds.count(subproductName));
        int subproductId = subproductIds[subproductName];
        assert(!suborderIds.count(name));
        int id = suborders.size();
        Suborder suborder{.id = id, .name = name, .subproductId = subproductId};
        suborders.push_back(suborder);
        suborderIds[name] = id;
    }
}

void readOrders(const XLWorksheet& xls) {
    int rowIt = 0;
    for (const auto& row : xls.rows()) {
        rowIt++;
        if (rowIt == 1)
            continue;
        std::vector<XLCellValue> values = row.values();
        string name = values[1];
        if (name.empty())
            break;
        int quantity = values[2];
        int price = values[4];
        int id = -1;
        if (!orderIds.count(name)) {
            id = orders.size();
            Order order{.id = id, .name = name, .quantity = quantity, .price = price};
            orders.push_back(order);
            orderIds[name] = id;
        } else {
            id = orderIds[name];
        }

        string suborderName = values[5];
        assert(suborderIds.count(suborderName));
        int suborderId = suborderIds[suborderName];
        orders[id].finalSuborders.push_back(suborderId);
    }
}

void readOrderGraph(const XLWorksheet& xls) {
    int rowIt = 0;
    for (const auto& row : xls.rows()) {
        rowIt++;
        if (rowIt == 1)
            continue;
        std::vector<XLCellValue> values = row.values();
        string fromName = values[1];
        if (fromName.empty())
            break;
        string toName = values[2];
        assert(suborderIds.count(fromName));
        assert(suborderIds.count(toName));
        int fromId = suborderIds[fromName];
        int toId = suborderIds[toName];
        suborders[fromId].outcomingSuborders.push_back(toId);
        suborders[toId].incomingSuborders.push_back(fromId);
    }
}

void readMovementTime(const XLWorksheet& xls) {
    int rowIt = 0;
    for (const auto& row : xls.rows()) {
        rowIt++;
        if (rowIt == 1)
            continue;
        std::vector<XLCellValue> values = row.values();
        string fromName = values[1];
        if (fromName.empty())
            break;
        string toName = values[2];
        if (!equipmentIds.count(fromName) || equipmentIds.count(toName))
            continue;
        int fromId = equipmentIds[fromName];
        int toId = equipmentIds[toName];

        string subproductName = values[3];
        assert(subproductIds.count(subproductName));
        int subproductId = subproductIds[subproductName];

        int duration = values[4];

        subproducts[subproductId].movementTimes[{fromId, toId}] = duration;
    }
}

void readInput(const string& filename) {
    XLDocument inputXls;
    inputXls.open(filename);
    std::streambuf* backup = cout.rdbuf();
    cout.rdbuf(nullptr);
    auto workbook = inputXls.workbook();
    readEquipments(workbook.worksheet("equipment"));
    readSubproducts(workbook.worksheet("subproduct"));
    readSwitchTimes(workbook.worksheet("switch_time"));
    readSuborders(workbook.worksheet("structure"));
    readOrders(workbook.worksheet("orders"));
    readOrderGraph(workbook.worksheet("order_graph"));
    readMovementTime(workbook.worksheet("movement_time"));
    cout.rdbuf(backup);
}

string toTwoDigitNumber(int x) {
    if (x < 10)
        return "0" + to_string(x);
    return to_string(x);
}

string minutesToDate(int minutes) {
    static int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = minutes / (24 * 60);
    int month = 0;
    for (int i = 0; i < 12; i++) {
        if (days < months[i])
            break;
        days -= months[i];
        month++;
    }
    minutes %= (24 * 60);
    int hours = minutes / 60;
    minutes %= 60;

    return toTwoDigitNumber(days + 1) + "." + toTwoDigitNumber(month + 1) + ".2022 " + toTwoDigitNumber(hours) + ":" + toTwoDigitNumber(minutes) + ":00";
}

void printOutput(const string& filename) {
    XLDocument outputXls;
    outputXls.create(filename);
    auto workbook = outputXls.workbook(); 
    workbook.addWorksheet("schedule");
    workbook.deleteSheet("Sheet1");
    auto worksheet = workbook.worksheet("schedule");
    worksheet.cell(1, 2).value() = "operation_type";
    worksheet.cell(1, 3).value() = "suborder_id";
    worksheet.cell(1, 4).value() = "equipment_id";
    worksheet.cell(1, 5).value() = "date_start";
    worksheet.cell(1, 6).value() = "date_fin";
    int row = 2;
    for (const Operation& operation : operations) {
        worksheet.cell(row, 1).value() = row - 2;
        worksheet.cell(row, 2).value() = 1 + int(operation.type);    
        worksheet.cell(row, 3).value() = suborders[operation.suborderId].name;
        worksheet.cell(row, 4).value() = equipments[operation.equipmentId].name;
        worksheet.cell(row, 5).value() = minutesToDate(operation.startTime);
        worksheet.cell(row, 6).value() = minutesToDate(operation.finishTime);
        row++;
    }
    outputXls.save();
    outputXls.close();
}

void print(int suborderId) {
    cout << "suborder id = " << suborderId << ", requirements = {";
    for (int fromId : suborders[suborderId].incomingSuborders)
        cout << fromId << ", ";
    cout << "}\n";

    for (int fromId : suborders[suborderId].incomingSuborders)
        print(fromId);
}

void analyzeData() {
    for (const auto& order : orders) {
        int duration = 0;
        multiset<int> ids;
        cout << "order: " << order.id << " name = " << order.name << " " << order.quantity << "\n";
        for (int id : order.finalSuborders) {
            print(id);
        }
        cout << "\n";
        cout << order.price << " " << order.quantity << " " << duration << "\n";
    }  
}

int dfs(int suborderId) {
    int subproductId = suborders[suborderId].subproductId;
    int minimumDuration = numeric_limits<int>::max();
    for (auto np : subproducts[subproductId].equipmentDurations) {
        minimumDuration = min(minimumDuration, np.second.first + np.second.second);
    }
    int minimumExecutionTime = 0;
    for (int fromId : suborders[suborderId].incomingSuborders) {
        minimumExecutionTime = max(minimumExecutionTime, dfs(fromId));
    }
    return minimumExecutionTime + minimumDuration;
}

vector<Order> filterOrders(const vector<Order>& orders, int totalDuration) {
    vector<Order> result;
    for (const Order& order : orders) {
        int minimumExecutionTime = 0;
        for (const int suborderId : order.finalSuborders) {
            minimumExecutionTime = max(minimumExecutionTime, dfs(suborderId));
        }
        if (order.quantity * minimumExecutionTime <= totalDuration) {
            result.push_back(order);
        }
    }
    return result;
}

vector<Suborder> filterSuborders(const vector<Suborder>& suborders, const unordered_map<int, int>& suborderOrder) {
    vector<Suborder> result;
    for (const Suborder& suborder : suborders) {
        if (suborderOrder.count(suborder.id))
            result.push_back(suborder);
    }
    return result;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        cout << "You need to specify 3 arguments: name of input xlsx file, name of output xlsx time and total duration for schedule in days\n";
        return 0;
    }
    readInput(argv[1]);
    int durationDays = atoi(argv[3]);
    int totalDuration = durationDays * 24 * 60;

    //analyzeData();

    // from equipment_id to list of <suborder_id, duration, switch_time>
    unordered_map<int, vector<tuple<int, int, int>>> equipmentSuborders; 
    for (const auto& suborder : suborders) {
        for (const auto& equipment : subproducts[suborder.subproductId].equipmentDurations) {
            equipmentSuborders[equipment.first].push_back({suborder.id, equipment.second.first, equipment.second.second});
        }
    }

    std::vector<Order> filteredOrders = filterOrders(orders, totalDuration);
    unordered_map<int, int> expectedExecutionTime;
    for (const Order& order : filteredOrders) {
        int minimumExecutionTime = 0;
        for (const int suborderId : order.finalSuborders) {
            minimumExecutionTime = max(minimumExecutionTime, dfs(suborderId));
        }
        expectedExecutionTime[order.id] = order.quantity * minimumExecutionTime;
    }

    unordered_map<int, int> suborderQuantities;
    unordered_map<int, int> suborderTotalQuantities;
    unordered_map<int, int> suborderOrder;
    for (const auto& order : filteredOrders) {
        queue<int> subordersQueue;
        for (int suborder : order.finalSuborders)
            subordersQueue.push(suborder);
        while (!subordersQueue.empty()) {
            int suborder = subordersQueue.front();
            suborderQuantities[suborder] = order.quantity;
            suborderOrder[suborder] = order.id;
            suborderTotalQuantities[suborder] += order.quantity;
            subordersQueue.pop();
            set<int> ids;
            for (int fromSuborder : suborders[suborder].incomingSuborders) {
                subordersQueue.push(fromSuborder);
                ids.insert(fromSuborder);
            }
        }
    }

    std::vector<Suborder> filteredSuborders = filterSuborders(suborders, suborderOrder);
    vector<int> allowedToProduce(suborders.size(), 0);
    for (const auto& suborder : filteredSuborders) {
        if (suborder.incomingSuborders.empty()) {
            allowedToProduce[suborder.id] = suborderTotalQuantities[suborder.id];
        }
    }

    struct ProducedSuborder {
        int timestamp;
        int equipmentId;

        bool operator<(const ProducedSuborder& other) const {
            if (timestamp != other.timestamp)
                return timestamp < other.timestamp;
            return equipmentId < other.equipmentId;
        }
    };
    unordered_map<int, set<ProducedSuborder>> availableSuborders;

    vector<Suborder> sortedSuborders = filteredSuborders;   
    vector<vector<int>> occupied(totalDuration, vector<int>(equipments.size()));
    vector<int> producedBatches(suborders.size(), 0);
    vector<int> producedCount(suborders.size(), 0);
    vector<int> totalProducedCount(suborders.size(), 0);
    set<tuple<int, int, int>> producedEvents;
    for (int t = 0; t < totalDuration; t++) {
        while (!producedEvents.empty() && get<0>(*producedEvents.begin()) <= t) {
            auto [timestamp, equipmentId, suborderId] = *producedEvents.begin();
            producedEvents.erase(producedEvents.begin());
            availableSuborders[suborderId].insert(ProducedSuborder{.timestamp = timestamp, .equipmentId = equipmentId});
            producedCount[suborderId]++;
            totalProducedCount[suborderId]++;
            if (producedCount[suborderId] >= suborderQuantities[suborderId]) {
                producedBatches[suborderId]++;
                producedCount[suborderId] -= suborderQuantities[suborderId];
            }
        }
        sort(sortedSuborders.begin(), sortedSuborders.end(), [&](const Suborder& l, const Suborder& r) {
            long long x = orders[suborderOrder[l.id]].price * 1ll * expectedExecutionTime[suborderOrder[r.id]];
            long long y = orders[suborderOrder[r.id]].price * 1ll * expectedExecutionTime[suborderOrder[l.id]];
            if (x != y)
                return x > y;
            return totalProducedCount[l.id] < totalProducedCount[r.id];
        });
        for (const auto& suborder : sortedSuborders) {
            if (allowedToProduce[suborder.id] == 0 && !suborder.incomingSuborders.empty()) {
                bool requirementsFulfilled = true;
                for (int fromId : suborder.incomingSuborders) {
                    if (producedBatches[fromId] == 0) {
                        requirementsFulfilled = false;
                        break;
                    }
                }
                if (!requirementsFulfilled)
                    continue;
                for (int fromId : suborder.incomingSuborders) {
                    producedBatches[fromId]--;
                }
                allowedToProduce[suborder.id] += suborderQuantities[suborder.id];
            }
        }
        for (const auto& suborder : sortedSuborders) {
            if (allowedToProduce[suborder.id] == 0)
                continue;
            int subproductId = suborder.subproductId;
            const auto& subproduct = subproducts[subproductId];

            int minimumFinishTimestamp = numeric_limits<int>::max();
            int minimumEquipmentId = -1;
            for (const auto& [equipmentId, durationPair] : subproducts[subproductId].equipmentDurations) {
                const auto& equipment = equipments[equipmentId];
                if (occupied[t][equipment.id])
                    continue;
                int finishTimestamp = 0;
                for (int fromId : suborder.incomingSuborders) {
                    auto& available = availableSuborders[fromId];
                    auto it = available.begin();
                    auto value = *it;
                    int fromEquipment = value.equipmentId;
                    int timestamp = value.timestamp;
                    auto movementTimeIt = subproduct.movementTimes.find({fromEquipment, equipment.id});
                    int movementTime = (movementTimeIt == subproduct.movementTimes.end() ? 0 : movementTimeIt->second);
                    finishTimestamp = max(finishTimestamp, timestamp + movementTime);
                }
                finishTimestamp += durationPair.first;
                if (finishTimestamp < minimumFinishTimestamp) {
                    minimumFinishTimestamp = finishTimestamp;
                    minimumEquipmentId = equipmentId;
                }
            }
            if (minimumEquipmentId != -1) {
                allowedToProduce[suborder.id]--;
                const auto& equipment = equipments[minimumEquipmentId];
                int maxIncomingTimestamp = 0;
                for (int fromId : suborder.incomingSuborders) {
                    auto& available = availableSuborders[fromId];
                    auto it = available.begin();
                    auto value = *it;
                    available.erase(it);
                    int fromEquipment = value.equipmentId;
                    int timestamp = value.timestamp;
                    auto movementTimeIt = subproduct.movementTimes.find({fromEquipment, equipment.id});
                    int movementTime = (movementTimeIt == subproduct.movementTimes.end() ? 0 : movementTimeIt->second);
                    maxIncomingTimestamp = max(maxIncomingTimestamp, timestamp + movementTime);
                }
            
                auto durationPair = subproducts[subproductId].equipmentDurations[equipment.id];
                int duration = durationPair.first;
                int switchTime = durationPair.second;
                int startTimestamp = max(maxIncomingTimestamp, t + switchTime);
                int finishTimestamp = startTimestamp + duration;
                if (finishTimestamp <= totalDuration) {
                    if (switchTime != 0) {
                        operations.push_back(Operation{.type = Operation::READJUSTMENT, .suborderId = suborder.id, .equipmentId = equipment.id, .startTime = startTimestamp - switchTime, .finishTime = startTimestamp});
                    }
                    operations.push_back(Operation{.type = Operation::MANUFACTURING, .suborderId = suborder.id, .equipmentId = equipment.id, .startTime = startTimestamp, .finishTime = finishTimestamp});
                    if (!equipment.mode) {
                        for (int j = t; j < finishTimestamp; j++)
                            occupied[j][equipment.id] = 1;
                    }
                    producedEvents.insert({finishTimestamp, equipment.id, suborder.id});
                }       
            }
        }
    }
    
    int totalIncome = 0;
    for (const auto& order : filteredOrders) {
        bool produced = true;
        for (int suborderId : order.finalSuborders) {
            if (producedBatches[suborderId] == 0) {
                produced = false;
                break;
            }
        }
        if (produced) {
            totalIncome += order.price;
        }
    }
    cout << "Total income: " << totalIncome << "\n";
    printOutput(argv[2]);

    return 0;
}
