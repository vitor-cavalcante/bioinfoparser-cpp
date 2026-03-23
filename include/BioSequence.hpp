/*
 * Project: BioInfoParser-CPP
 * Author: Vitor Cavalcante
 * License: MIT
 */

#pragma once

#include <string>
#include <string_view>

namespace BioInfoParser
{

    /**
     * @class BioSequence
     * @brief Represents a biological sequence (DNA, RNA, or Protein).
     * * This class stores the sequence data along with a unique identifier
     * and provides methods for basic bioinformatics analysis.
     */
    class BioSequence
    {
    private:
        std::string identifier; // Unique name or accession number for the sequence.
        std::string sequence;   // Raw sequence data (e.g., "ACTG").

    public:
        /**
         * @brief Constructs a BioSequence object.
         * @param id The sequence identifier.
         * @param seq The raw sequence string.
         */
        BioSequence(std::string_view id, std::string_view seq)
            : identifier(id), sequence(seq) {}

        // Getters
        [[nodiscard]] std::string_view get_identifier() const noexcept { return identifier; }
        [[nodiscard]] std::string_view get_sequence() const noexcept { return sequence; }
        [[nodiscard]] size_t get_length() const noexcept { return sequence.length(); }

        /**
         * @brief Calculates the GC content percentage of the sequence.
         * @return Double representing the (G+C)/Total ratio * 100.
         */
        [[nodiscard]] double get_gc_content() const noexcept;

        /**
         * @brief Generates the reverse complement of a DNA sequence.
         * @return A new string containing the reverse complement.
         */
        [[nodiscard]] std::string get_reverse_complement() const noexcept;

        /**
         * @brief Transcribes a DNA sequence into RNA.
         * @return A new string where Thymine (T) is replaced by Uracil (U).
         */
        [[nodiscard]] std::string get_rna_transcription() const noexcept;
    };

} // namespace BioInfoParser