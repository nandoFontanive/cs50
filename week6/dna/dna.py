import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print(f"Error. First argument must be CSV file and second argument must be text file with DNA sequence")
    elif len(sys.argv) == 3:

        # TODO: Read database file into a variable
        with open(sys.argv[1]) as file:
            reader = csv.DictReader(file)
            rows = []
            for row in reader:
                rows.append(row)

    # TODO: Read DNA sequence file into a variable
        with open(sys.argv[2]) as file2:
            fileasstring = file2.read()

    # TODO: Find longest match of each STR in DNA sequence
        contagem_sequencia = []
        for padrao in reader.fieldnames[1:]:
            max_repeticoes = 0
            # print(f"padrao {padrao}:")
            while (padrao * (max_repeticoes + 1)) in fileasstring:
                max_repeticoes += 1
            contagem_sequencia.append(max_repeticoes)
            # print(f"O número máximo de repetições consecutivas para '{padrao}' é: {max_repeticoes}")
            # print(contagem_sequencia)

    # TODO: Check database for matching profiles
        nomes_campos = reader.fieldnames[1:]

        for pessoa in rows:
            match = True
            for i in range(len(nomes_campos)):
                str_nome = nomes_campos[i]
                if int(pessoa[str_nome]) != contagem_sequencia[i]:
                    match = False
                    break
            if match:
                print(pessoa["name"])
                return

        print("No match")
        return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
