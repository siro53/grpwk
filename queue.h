#define QUE_TYPE int

const int MAX_SIZE = 500000;

typedef struct
{
    QUE_TYPE data[MAX_SIZE];
    QUE_TYPE front;
    QUE_TYPE back;
} queue;

void que_init(queue *que, QUE_TYPE init_value);
void que_push(queue *que, QUE_TYPE value);
void que_pop(queue *que);
QUE_TYPE que_size(queue *que);