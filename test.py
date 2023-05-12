class State:
    NORMAL, SINGLE_QUOTE, DOUBLE_QUOTE, PIPE, ENV_VAR, REDIRECTION = range(6)

def tokenize(input):
    tokens = []
    current_token = ""
    current_state = State.NORMAL

    for char in input:
        if current_state == State.NORMAL:
            if char == '\'':
                current_state = State.SINGLE_QUOTE
                current_token = ""
            elif char == '\"':
                current_state = State.DOUBLE_QUOTE
                current_token = ""
            elif char == '|':
                tokens.append(current_token.strip())
                tokens.append(char)
                current_token = ""
            elif char == '$':
                current_state = State.ENV_VAR
                current_token = char
            elif char == '>':
                tokens.append(current_token.strip())
                tokens.append(char)
                current_token = ""
            else:
                current_token += char
        elif current_state == State.SINGLE_QUOTE:
            if char == '\'':
                current_state = State.NORMAL
                tokens.append(current_token)
                current_token = ""
            else:
                current_token += char
        elif current_state == State.DOUBLE_QUOTE:
            if char == '\"':
                current_state = State.NORMAL
                tokens.append(current_token)
                current_token = ""
            else:
                current_token += char
        elif current_state == State.ENV_VAR:
            if char == ' ':
                current_state = State.NORMAL
                tokens.append(current_token)
                current_token = ""
            else:
                current_token += char
    if current_token:
        tokens.append(current_token.strip())
    return tokens

print(tokenize(input("$_ ")))
