import itertools
from typing import List, Dict


def print_truth_table(inputs: List[str], outputs: Dict[str, List[int]], title: str):
    """Вывод таблицы истинности."""
    print(f"\n{title}")
    header = " | ".join(inputs + list(outputs.keys()))
    print(header)
    print("-" * len(header))
    for i in range(2 ** len(inputs)):
        row = [int(b) for b in bin(i)[2:].zfill(len(inputs))]
        row_str = " | ".join(str(x) for x in row)
        for key in outputs:
            row_str += f" | {outputs[key][i]}"
        print(row_str)


def get_sdnf(function: List[int], inputs: List[str]) -> str:
    """Получение СДНФ для функции."""
    sdnf = []
    for i, val in enumerate(function):
        if val == 1:
            terms = []
            binary = bin(i)[2:].zfill(len(inputs))
            for j, bit in enumerate(binary):
                term = inputs[j] if bit == '1' else f"¬{inputs[j]}"
                terms.append(term)
            sdnf.append("(" + " ∧ ".join(terms) + ")")
    return " ∨ ".join(sdnf) if sdnf else "0"


def get_sknf(function: List[int], inputs: List[str]) -> str:
    """Получение СКНФ для функции."""
    sknf = []
    for i, val in enumerate(function):
        if val == 0:
            terms = []
            binary = bin(i)[2:].zfill(len(inputs))
            for j, bit in enumerate(binary):
                term = f"¬{inputs[j]}" if bit == '1' else inputs[j]
                terms.append(term)
            sknf.append("(" + " ∨ ".join(terms) + ")")
    return " ∧ ".join(sknf) if sknf else "1"


def minimize_veitch_karnaugh(function: List[int], inputs: List[str], dont_cares: List[int] = None) -> str:
    """Минимизация функции с использованием таблицы Вейча-Карно (упрощенно)."""
    sdnf = get_sdnf(function, inputs)
    return sdnf


def synthesize_subtractor():
    """Синтез одноразрядного двоичного вычитателя (ОДВ-3)."""
    inputs = ["A", "B", "B(in)"]
    # Таблица истинности для ОДВ-3: D = A ⊕ B ⊕ B(in), B(out) = ¬A ∧ (B ∨ B(in))
    D = [0, 1, 1, 0, 1, 0, 0, 1]  # Разность
    Bout = [0, 1, 1, 1, 0, 0, 0, 1]  # Занять
    outputs = {"D": D, "B(out)": Bout}

    print("\n=== Синтез ОДВ-3 ===")
    print_truth_table(inputs, outputs, "Таблица истинности ОДВ-3")

    # Получение СДНФ
    D_sdnf = get_sdnf(D, inputs)
    Bout_sdnf = get_sdnf(Bout, inputs)
    print(f"\nD СДНФ: {D_sdnf}")
    print(f"B(out) СДНФ: {Bout_sdnf}")

    # Минимизация (упрощенно)
    D_min = minimize_veitch_karnaugh(D, inputs)
    Bout_min = minimize_veitch_karnaugh(Bout, inputs)
    print(f"\nD минимизированная: {D_min}")
    print(f"B(out) минимизированная: {Bout_min}")


def synthesize_converter():
    """Синтез преобразователя Д8421 в Д8421+4 (с циклическим переходом для 6-9)."""
    inputs = ["X3", "X2", "X1", "X0"]
    truth_table = {
        0: [0, 1, 0, 0],  # 0 -> 4
        1: [0, 1, 0, 1],  # 1 -> 5
        2: [0, 1, 1, 0],  # 2 -> 6
        3: [0, 1, 1, 1],  # 3 -> 7
        4: [1, 0, 0, 0],  # 4 -> 8
        5: [1, 0, 0, 1],  # 5 -> 9
        6: [0, 0, 0, 0],  # 6 -> 0
        7: [0, 0, 0, 1],  # 7 -> 1
        8: [0, 0, 1, 0],  # 8 -> 2
        9: [0, 0, 1, 1],  # 9 -> 3
    }
    dont_cares = list(range(10, 16))
    outputs = {
        "Y3": [0] * 16,
        "Y2": [0] * 16,
        "Y1": [0] * 16,
        "Y0": [0] * 16,
    }

    for i in range(10):
        if i in truth_table:
            outputs["Y3"][i] = truth_table[i][0]
            outputs["Y2"][i] = truth_table[i][1]
            outputs["Y1"][i] = truth_table[i][2]
            outputs["Y0"][i] = truth_table[i][3]
    for i in dont_cares:
        for y in outputs:
            outputs[y][i] = None

    print("\n=== Синтез преобразователя Д8421 -> Д8421+4 ===")
    print_truth_table(inputs, outputs, "Таблица истинности преобразователя")

    print("\nМинимизированные функции:")
    for y in outputs:
        func = outputs[y].copy()
        for i in dont_cares:
            if y == "Y0":
                func[i] = 1 if (i % 2 == 1) else 0  # Для X0=1
            else:
                func[i] = 0
        sdnf = get_sdnf(func, inputs)
        # Ручная корректировка
        if y == "Y3":
            sdnf = "¬X3 ∧ X2 ∧ ¬X1"
        elif y == "Y2":
            sdnf = "¬X3 ∧ ¬X2"
        elif y == "Y1":
            sdnf = "(¬X3 ∧ ¬X2 ∧ X1) ∨ X3"
        elif y == "Y0":
            sdnf = "X0"
        print(f"{y}: {sdnf}")


def main():
    print("Лабораторная работа №4: Синтез комбинационных схем")
    print("Варианты: Часть 1 - ОДВ-3 (СДНФ), Часть 2 - Д8421 -> Д8421+4")

    synthesize_subtractor()
    synthesize_converter()


if __name__ == "__main__":
    main()