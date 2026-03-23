/*
 * Project: BioInfoParser-CPP
 * Author: Vitor Cavalcante
 * License: MIT
 */

#pragma once

#include <string>
#include <fstream>
#include "BioSequence.hpp"

namespace BioInfoParser
{

    /**
     * @class ReportGenerator
     * @brief Manages the generation of output files for processed sequences and statistics.
     * * This class handles multiple output streams to provide both a processed FASTA file
     * and a human-readable summary of biological metrics such as GC content and length.
     */
    class ReportGenerator
    {
    private:
        std::ofstream fasta_out; // Output stream for processed biological sequences.
        std::ofstream stats_out; // Output stream for sequence analysis reports.

    public:
        /**
         * @brief Initializes output streams using a base filename.
         * @param base_filename The prefix used to create .processed.fasta and .stats.txt files.
         */
        explicit ReportGenerator(const std::string &base_filename);

        /**
         * @brief Destructor ensures all output streams are properly flushed and closed.
         */
        ~ReportGenerator();

        /**
         * @brief Writes a BioSequence object to the FASTA output file.
         * @param seq The sequence to be exported.
         */
        void write_to_fasta(const BioSequence &seq);

        /**
         * @brief Writes metrics (GC content, length) of a sequence to the report file.
         * @param seq The sequence to be analyzed.
         */
        void write_to_stats(const BioSequence &seq);

        /**
         * @brief Writes a formatted header to the beginning of the statistics report.
         */
        void write_header();
    };

} // namespace BioInfoParser