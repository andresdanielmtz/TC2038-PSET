def test(x: int) -> None:
    if x == 0:
        print("It's zero!")
        return
    test(x - 1)

    print(f"X: {x}")

test(10)