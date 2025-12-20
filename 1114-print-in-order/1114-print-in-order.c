typedef struct {
    // User defined data may be declared here.
    int turn;
    pthread_mutex_t mut;
    pthread_cond_t cond;
} Foo;

// Function Declaration, do not remove
void printFirst();
void printSecond();
void printThird();

Foo* fooCreate() {
    Foo* obj = (Foo*) malloc(sizeof(Foo));
    
    // Initialize user defined data here.
    obj->turn = 1;
    pthread_mutex_init(&(obj->mut), NULL);
    pthread_cond_init(&(obj->cond), NULL);

    return obj;
}

void first(Foo* obj) {
    pthread_mutex_lock(&(obj->mut));
    while (obj->turn != 1) {
        pthread_cond_wait(&(obj->cond), &(obj->mut));
    }
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    obj->turn = 2;
    pthread_mutex_unlock(&(obj->mut));
    pthread_cond_broadcast(&(obj->cond));
}

void second(Foo* obj) {
    pthread_mutex_lock(&(obj->mut));
    while (obj->turn != 2) {
        pthread_cond_wait(&(obj->cond), &(obj->mut));
    }
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    obj->turn = 3;
    pthread_mutex_unlock(&(obj->mut));
    pthread_cond_broadcast(&(obj->cond));
}

void third(Foo* obj) {
    pthread_mutex_lock(&(obj->mut));
    while (obj->turn != 3) {
        pthread_cond_wait(&(obj->cond), &(obj->mut));
    }
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
    obj->turn = 1;
    pthread_mutex_unlock(&(obj->mut));
    pthread_cond_broadcast(&(obj->cond));
}

void fooFree(Foo* obj) {
    // User defined data may be cleaned up here.
    pthread_mutex_destroy(&(obj->mut));
    pthread_cond_destroy(&(obj->cond));
    free(obj);
}