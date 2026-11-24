from cs50 import get_string

# define main e dentro dela fica o aviso que usarei essas funcoes (validade_text, check_grade, etc)


def main():
    # recebo a variavel text do user
    text = get_string("Text: ")

    # rodo a função ainda não descrita validate_text no texto inserido pelo user
    text = validate_text(text)

    # crio outras variaveis tb usando funcoes ainda não definidas
    number_spaces = count_spaces(text)
    number_sentences = count_sentences(text)
    number_words = number_spaces + 1
    number_letters = count_letters(text)
    grade = check_grade(number_letters, number_words, number_sentences)
    if grade < 2:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade:.0f}")

# começo a definir as funções utilizadas acima


def check_grade(number_letters, number_words, number_sentences):
    average_letters = (number_letters / number_words)
    average_sentences = (number_sentences / number_words)
    index = ((0.0588 * average_letters * 100) - (0.296 * average_sentences * 100) - 15.8)
    return round(index)


def count_letters(text):
    number_letters = 0
    for i in range(len(text)):
        if text[i].isalpha():
            number_letters += 1
    return number_letters


def count_spaces(text):
    number_spaces = 0
    for i in range(len(text)):
        if text[i] == " ":
            number_spaces += 1
    return number_spaces


def count_sentences(text):
    number_sentences = 0
    for i in range(len(text)):
        if text[i] == "." or text[i] == "?" or text[i] == "!":
            number_sentences += 1
    return number_sentences


def validate_text(text):
    while len(text) == 0 or text[0] == " " or text[0] == "." or text[0] == "!" or text[0] == "?":
        print("Please enter a valid text")
        text = get_string("Text: ")
    return text


# final do programa com if da main
if __name__ == "__main__":
    main()
