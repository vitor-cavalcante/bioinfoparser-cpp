/*
 * Project: BioInfoParser-CPP
 * Author: Vitor Cavalcante
 * License: MIT
 */

#pragma once

#include <string>
#include <fstream>
#include <optional>
#include "BioSequence.hpp"

namespace BioInfoParser
{

    /**
     * @class FastaParser
     * @brief Handles the reading and parsing of FASTA formatted files.
     * * This class manages the file stream and provides an interface to extract
     * biological sequences one by one, ensuring efficient memory usage by
     * processing the file line by line.
     */
    class FastaParser
    {
    private:
        std::ifstream input_file; // Stream for reading the FASTA file data.
        std::string last_line;    // Stores the lookahead header line (starting with '>') to identify new sequences.

    public:
        /**
         * @brief Initializes the parser and opens the target file.
         * @param filepath Path to the input FASTA file.
         * @throw std::runtime_error If the file cannot be opened.
         */
        explicit FastaParser(const std::string &filepath);

        /**
         * @brief Destructor ensures the file stream is properly closed.
         */
        ~FastaParser();

        /**
         * @brief Checks if there are remaining sequences to be processed.
         * @return true if the end of file (EOF) has not been reached, false otherwise.
         */
        [[nodiscard]] bool has_more_sequences();

        /**
         * @brief Extracts the next sequence from the file.
         * @return std::optional containing the BioSequence if successful, or std::nullopt if EOF is reached.
         */
        [[nodiscard]] std::optional<BioSequence> get_next_sequence();
    };

} // namespace BioInfoParser