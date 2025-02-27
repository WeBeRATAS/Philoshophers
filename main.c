int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso: %s <número_de_filósofos>\n", argv[0]);
        return 1;
    }

    int num_philosophers = atoi(argv[1]);
    t_data data;

    init_data(&data, num_philosophers);
    start_simulation(&data);
    cleanup(&data);

    return 0;
}
