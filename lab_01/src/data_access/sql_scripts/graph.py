import matplotlib.pyplot as plt
def build_graph():
    size = [10, 100, 500, 1000, 5000, 10000, 50000, 100000]
    no_idx = [17, 19, 22, 25, 28, 32, 37, 47]
    idx_btree = [13, 15, 16, 17, 18, 19, 20, 24]
    idx_hash = [14, 16, 17, 18, 19, 20, 21, 23]

    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(size, no_idx, label='Без индекса')
    plot.plot(size, idx_btree, label='Индекс unique c методом btree')
    plot.plot(size, idx_hash, label='Индекс с методом hash')

    plt.legend()
    plt.grid()
    plt.title("Зависимость времени ответа БД от размера таблицы")
    plt.ylabel("Время выборки, мс")
    plt.xlabel("Количество записей в таблице, шт.")
    plt.legend()

    plt.show()


def main():
    build_graph()


if __name__ == "__main__":
    main()