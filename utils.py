REV_BASE62 = {'a': 49, 'b': 23, 'c': 29, 'd': 26, 'e': 22, 'f': 60, 'g': 50, 'h': 30, 'i': 43, 'j': 48, 'k': 3, 'l': 34, 'm': 0, 'n': 61, 'o': 12, 'p': 59, 'q': 53, 'r': 31, 's': 54, 't': 56, 'u': 15, 'v': 27, 'w': 35, 'x': 46, 'y': 41, 'z': 44, 'A': 57, 'B': 42, 'C': 6, 'D': 20, 'E': 14, 'F': 55, 'G': 1, 'H': 58, 'I': 45, 'J': 37, 'K': 19, 'L': 38, 'M': 4, 'N': 2, 'O': 47, 'P': 28, 'Q': 51, 'R': 24, 'S': 10, 'T': 17, 'U': 9, 'V': 33, 'W': 13, 'X': 7, 'Y': 32, 'Z': 5, '0': 18, '1': 39, '2': 8, '3': 21, '4': 11, '5': 16, '6': 36, '7': 40, '8': 25, '9': 52}

FWD_BASE62 = {49: 'a', 23: 'b', 29: 'c', 26: 'd', 22: 'e', 60: 'f', 50: 'g', 30: 'h', 43: 'i', 48: 'j', 3: 'k', 34: 'l', 0: 'm', 61: 'n', 12: 'o', 59: 'p', 53: 'q', 31: 'r', 54: 's', 56: 't', 15: 'u', 27: 'v', 35: 'w', 46: 'x', 41: 'y', 44: 'z', 57: 'A', 42: 'B', 6: 'C', 20: 'D', 14: 'E', 55: 'F', 1: 'G', 58: 'H', 45: 'I', 37: 'J', 19: 'K', 38: 'L', 4: 'M', 2: 'N', 47: 'O', 28: 'P', 51: 'Q', 24: 'R', 10: 'S', 17: 'T', 9: 'U', 33: 'V', 13: 'W', 7: 'X', 32: 'Y', 5: 'Z', 18: '0', 39: '1', 8: '2', 21: '3', 11: '4', 16: '5', 36: '6', 40: '7', 25: '8', 52: '9'}

CARD_TYPES = {0: 'NONE', 1: 'TOOL', 2: 'LULLABY', 3: 'HAT', 4: 'MASK', 5: 'SWAP', 6: 'DISMEMBER', 7: 'WILD_PROVOKE', 8: 'C_TORSO', 9: 'TORSO', 10: 'M_BODY', 11: 'AL_BODY', 12: 'LEGS', 13: 'ARM', 17: 'LAND', 23: 'SKY', 29: 'BEAR'}

ACTIONS = {1: 'DRAW', 2: 'PLAY_CARD', 200: 'PROVOKE', 240: 'DUMPSTER_DIVE'}


def convert_62_f(x):
    s = ""
    while x:
        s = FWD_BASE62[x%62] + s
        x //= 62
    return s

def convert_62_r(s):
    x = 0
    for c in s:
        x *= 62
        x += REV_BASE62[c]
    return x




if __name__ == '__main__':
    import numpy as np
    arr = np.random.permutation(62)

    for i in range(ord("a"), ord("z")+1):
        FWD_BASE62[chr(i)] = arr[i-ord("a")]
        REV_BASE62[arr[i-ord("a")]] = chr(i)
    for i in range(ord("A"), ord("Z")+1):
        FWD_BASE62[chr(i)] = arr[i+26-ord("A")]
        REV_BASE62[arr[i+26-ord("A")]] = chr(i)
    for i in range(ord("0"), ord("9")+1):
        FWD_BASE62[chr(i)] = arr[i+52-ord("0")]
        REV_BASE62[arr[i+52-ord("0")]] = chr(i)

    print(FWD_BASE62)
    print(REV_BASE62)
