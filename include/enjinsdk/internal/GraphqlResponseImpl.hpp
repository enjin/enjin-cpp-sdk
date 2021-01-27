#ifndef ENJINCPPSDK_GRAPHQLRESPONSEIMPL_HPP
#define ENJINCPPSDK_GRAPHQLRESPONSEIMPL_HPP

#include "enjinsdk/models/PaginationCursor.hpp"
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace enjin::sdk::graphql {

/// \brief Extracts the boolean result from the data JSON.
/// \param data_json The JSON.
/// \return Optional with the boolean result.
std::optional<bool> get_bool_result(const std::string& data_json);

/// \brief Extracts the pagination cursor and serialized items array from the data JSON.
/// \param data_json The JSON.
/// \return Optional with the pagination cursor and serialized items array.
std::optional<std::pair<models::PaginationCursor, std::vector<std::string>>>
get_pagination_tuple(const std::string& data_json);

/// \brief Extracts the serialized result objects array from the data JSON.
/// \param data_json The JSON.
/// \return Optional with the serialized result objects.
std::optional<std::vector<std::string>> get_serialized_object_array(const std::string& data_json);

/// \brief Extracts the serialized result object from the data JSON.
/// \param data_json The JSON.
/// \return Optional with the serialized result object.
std::optional<std::string> get_serialized_result_object(const std::string& data_json);

/// \brief Determines if the given JSON has pagination data from the platform.
/// \param data_json The JSON.
/// \return Whether the data JSON has pagination data.
bool is_json_paginated(const std::string& data_json);

}

#endif //ENJINCPPSDK_GRAPHQLRESPONSEIMPL_HPP
