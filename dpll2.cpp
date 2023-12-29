// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <unordered_set>
// #include <unordered_map>
// #include <sstream>
// #include <string>

// bool dpll2(std::vector<std::vector<int>> cnf, std::unordered_map<int, bool>&
// assignment) {
//     bool satisfied = true;

//     // Unit propagation
//     auto clause = cnf.begin();
//     while (clause != cnf.end()) {
//         if (clause->size() == 1) {
//             // encountered unit clause
//             int literal = clause->front();
//             clause = cnf.erase(clause);
//             assignment[std::abs(literal)] = (literal > 0);
//             for (auto clause : cnf) {
//                 clause.erase(std::remove(clause.begin(), clause.end(),
//                 -literal),
//                                       clause.end());
//             }
//         } else {
//             ++clause;
//         }
//     }

//     std::unordered_set<int> pureLiterals;

//     //pure literal elimination
//     for (const auto& clause : cnf) {
//         for (int literal : clause) {
//             int var = std::abs(literal);
//             if (pureLiterals.find(var) == pureLiterals.end()) {
//                 // Check if the opposite of the literal exists in other
//                 clauses bool oppositeFound = false; for (const auto&
//                 otherClause : cnf) {
//                     if (std::find(otherClause.begin(), otherClause.end(),
//                     -literal) != otherClause.end()) {
//                         oppositeFound = true;
//                         break;
//                     }
//                 }

//                 if (!oppositeFound) {
//                     pureLiterals.insert(var);
//                     assignment[var] = (literal > 0); // Assign the pure
//                     literal
//                 }
//             }
//         }
//     }

//     // Remove clauses containing pure literals
//     cnf.erase(std::remove_if(cnf.begin(), cnf.end(),
//         [&pureLiterals](const std::vector<int> clause) {
//             for (int literal : clause) {
//                 if (pureLiterals.find(std::abs(literal)) !=
//                 pureLiterals.end()) {
//                     return true; // Remove clauses with pure literals
//                 }
//             }
//             return false;
//         }), cnf.end());

//     // Check for satisfied clauses
//     for (const auto& clause : cnf) {
//         bool clauseSatisfied = false;
//         for (int literal : clause) {
//             if (assignment.count(std::abs(literal)) &&
//             (assignment[std::abs(literal)] == (literal > 0))) {
//                 clauseSatisfied = true;
//                 break;
//             }
//         }
//         if (!clauseSatisfied) {
//             satisfied = false;
//             break;
//         }
//     }

//     if (satisfied) {
//         return true;
//     }

//     // Choose an unassigned variable
//     int literal = 0;
//     for (const auto& clause : cnf) {
//         for (int l : clause) {
//             if (!assignment.count(std::abs(l))) {
//                 literal = l;
//                 break;
//             }
//         }
//         if (literal != 0) {
//             break;
//         }
//     }

//     if (literal != 0) {
//         // Try assigning true
//         cnf.push_back({{literal}});
//         std::unordered_map<int, bool> assignmentTrue = assignment;
//         assignmentTrue[std::abs(literal)] = (literal > 0);
//         if (dpll(cnf, assignmentTrue)) {
//             assignment = assignmentTrue;
//             return true;
//         }

//         // Try assigning false
//         cnf.back().front() = -literal;
//         std::unordered_map<int, bool> assignmentFalse = assignment;
//         assignmentFalse[std::abs(literal)] = !(literal > 0);
//         if (dpll(cnf, assignmentFalse)) {
//             assignment = assignmentFalse;
//             return true;
//         }
//     }

//     return false; // Conflict or unsatisfiable
// }
