#include "route_planner.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {

    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*end_node);
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();

    for (auto neighbor : current_node->neighbors) {
        neighbor->parent = current_node;
        neighbor->h_value = CalculateHValue(neighbor);
        neighbor->g_value = current_node->distance(*neighbor) + current_node->g_value;

        open_list.push_back(neighbor);

        neighbor->visited = true;
    }
}

bool is_bigger(RouteModel::Node* a, RouteModel::Node* b) {
    return a->g_value + a->h_value > b->g_value + b->h_value;
}

RouteModel::Node *RoutePlanner::NextNode() {

    std::sort(open_list.begin(), open_list.end(), is_bigger);

    RouteModel::Node *lowest_sum_node = open_list.back();

    open_list.pop_back();

    return lowest_sum_node;
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    while (current_node->parent != 0) {

        path_found.push_back(*current_node);
        float node_to_parent_distance = current_node->distance(*current_node->parent);

        distance += node_to_parent_distance;
    }

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    start_node->visited = true;

    open_list.push_back(start_node);

    while (open_list.size() > 0) {

        AddNeighbors(current_node);

        current_node = NextNode();

        if (current_node->distance(*end_node) == 0) {
            m_Model.path = ConstructFinalPath(current_node);
        }
    }
}
