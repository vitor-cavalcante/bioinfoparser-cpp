/*
 * Project: BioInfoParser-CPP
 * Author: Vitor Cavalcante
 * License: MIT
 */

#include "BioSequence.hpp"
#include <algorithm>
#include <cctype> // Required for std::toupper

namespace BioInfoParser
{

    /**
     * Calculates the GC content percentage of the sequence.
     * GC content is the percentage of nitrogenous bases in a DNA/RNA molecule
     * that are either Guanine (G) or Cytosine (C).
     */
    double BioSequence::get_gc_content() const noexcept
    {
        if (sequence.empty())
        {
            return 0.0;
        }

        size_t gc_count = 0;
        for (char base : sequence)
        {
            char upper_base = static_cast<char>(std::toupper(static_cast<unsigned char>(base)));
            if (upper_base == 'G' || upper_base == 'C')
            {
                gc_count++;
            }
        }

        return (static_cast<double>(gc_count) / sequence.length()) * 100.0;
    }

    /**
     * Generates the reverse complement of the DNA sequence.
     * This involves reversing the string and replacing each base with its
     * complementary partner (A-T, C-G).
     */
    std::string BioSequence::get_reverse_complement() const noexcept
    {
        std::string rev_comp = sequence;

        // 1. Reverse the sequence string
        std::reverse(rev_comp.begin(), rev_comp.end());

        // 2. Map each base to its complement
        for (char &base : rev_comp)
        {
            switch (static_cast<char>(std::toupper(static_cast<unsigned char>(base))))
            {
            case 'A':
                base = 'T';
                break;
            case 'T':
                base = 'A';
                break;
            case 'C':
                base = 'G';
                break;
            case 'G':
                base = 'C';
                break;
            default:
                break; // Keep unknown bases (like 'N') as they are
            }
        }
        return rev_comp;
    }

    /**
     * Transcribes DNA to RNA.
     * In this process, every instance of Thymine (T) is replaced by Uracil (U).
     */
    std::string BioSequence::get_rna_transcription() const noexcept
    {
        std::string rna = sequence;
        for (char &base : rna)
        {
            if (static_cast<char>(std::toupper(static_cast<unsigned char>(base))) == 'T')
            {
                base = 'U';
            }
        }
        return rna;
    }

} // namespace BioInfoParser