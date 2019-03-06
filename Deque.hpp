#ifndef MS_DEQUE_H
#define MS_DEQUE_H

#define Deque_DEFINE(t)                                                                                                                    \
    using namespace std;                                                                                                                   \
    struct Deque_##t;                                                                                                                      \
    struct Deque_##t##_Iterator;                                                                                                           \
    struct Deque_##t {                                                                                                                     \
        char type_name[(sizeof "Deque_") + (sizeof #t) - 1];                                                                               \
        t *t##_ldata;                                                                                                                      \
        int dq_frnt_idx;                                                                                                                   \
        int dq_bck_idx;                                                                                                                    \
        size_t dq_capacity;                                                                                                                \
        size_t dq_size;                                                                                                                    \
        size_t (*size)(Deque_##t *deq);                                                                                                    \
        bool (*empty)(Deque_##t *deq);                                                                                                     \
        Deque_##t##_Iterator (*begin)(Deque_##t *deq);                                                                                     \
        Deque_##t##_Iterator (*end)(Deque_##t *deq);                                                                                       \
        t& (*at)(Deque_##t *deq, size_t i);                                                                                                \
        void (*clear)(Deque_##t *deq);                                                                                                     \
        void (*push_back)(Deque_##t *deq, t);                                                                                              \
        void (*push_front)(Deque_##t *deq, t);                                                                                             \
        t& (*front)(Deque_##t *deq);                                                                                                       \
        t& (*back)(Deque_##t *deq);                                                                                                        \
        void (*pop_front)(Deque_##t *deq);                                                                                                 \
        void (*pop_back)(Deque_##t *deq);                                                                                                  \
        void (*dtor)(Deque_##t *deq);                                                                                                      \
        bool (*comp)(const t &o1, const t &o2);                                                                                            \
        void (*sort)(Deque_##t *deq, Deque_##t##_Iterator begin, Deque_##t##_Iterator end);                                                \
    };                                                                                                                                     \
    struct Deque_##t##_Iterator {                                                                                                          \
        struct Deque_##t *deque_##t;                                                                                                       \
        int deque_##t##_index;                                                                                                             \
        void (*inc)(Deque_##t##_Iterator *it);                                                                                             \
        void (*dec)(Deque_##t##_Iterator *it);                                                                                             \
        t& (*deref)(Deque_##t##_Iterator *it);                                                                                             \
    };                                                                                                                                     \
    typedef struct Deque_##t##_Iterator Deque_##t##_Iterator;                                                                              \
    typedef struct Deque_##t Deque_##t;                                                                                                    \
    size_t deque_size(Deque_##t *deq) {                                                                                                    \
        return deq->dq_size;                                                                                                               \
    }                                                                                                                                      \
    bool deque_empty(Deque_##t *deq) {                                                                                                     \
        return (0 == deq->dq_size);                                                                                                        \
    }                                                                                                                                      \
    void deque_clear(Deque_##t *deq) {                                                                                                     \
        deq->dq_size = 0;                                                                                                                  \
        deq->dq_frnt_idx = -1;                                                                                                             \
        deq->dq_bck_idx = 0;                                                                                                               \
    }                                                                                                                                      \
    bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2) {                                                                               \
        if (deq1.dq_size != deq2.dq_size) {                                                                                                \
            return false;                                                                                                                  \
        }                                                                                                                                  \
        for (size_t i = 0; i < deq1.dq_size; ++i) {                                                                                        \
            t t##_1 = deq1.at(&deq1, i);                                                                                                   \
            t t##_2 = deq2.at(&deq2, i);                                                                                                   \
            if (deq1.comp(t##_1, t##_2) || deq2.comp(t##_2, t##_1)) {                                                                      \
                return false;                                                                                                              \
            }                                                                                                                              \
        }                                                                                                                                  \
        return true;                                                                                                                       \
    }                                                                                                                                      \
    void deque_inc(Deque_##t##_Iterator *it) {                                                                                             \
        it->deque_##t##_index++;                                                                                                           \
    }                                                                                                                                      \
    void deque_dec(Deque_##t##_Iterator *it) {                                                                                             \
        it->deque_##t##_index--;                                                                                                           \
    }                                                                                                                                      \
    t& deque_deref(Deque_##t##_Iterator *it) {                                                                                             \
        Deque_##t *deq_##t = it->deque_##t;                                                                                                \
        int index = deq_##t->dq_frnt_idx - it->deque_##t##_index;                                                                          \
        if (index < 0) {                                                                                                                   \
            index = index + deq_##t->dq_capacity;                                                                                          \
        }                                                                                                                                  \
        return deq_##t->t##_ldata[index];                                                                                                  \
    }                                                                                                                                      \
    Deque_##t##_Iterator deque_begin(Deque_##t *deq) {                                                                                     \
        Deque_##t##_Iterator t##_iter{};                                                                                                   \
        t##_iter.deque_##t = deq;                                                                                                          \
        t##_iter.deque_##t##_index = 0;                                                                                                    \
        t##_iter.inc = &deque_inc;                                                                                                         \
        t##_iter.deref = &deque_deref;                                                                                                     \
        t##_iter.dec = &deque_dec;                                                                                                         \
        return t##_iter;                                                                                                                   \
    }                                                                                                                                      \
    Deque_##t##_Iterator deque_end(Deque_##t *deq) {                                                                                       \
        Deque_##t##_Iterator t##_iter{};                                                                                                   \
        t##_iter.deque_##t = deq;                                                                                                          \
        t##_iter.deque_##t##_index = deq->dq_size;                                                                                         \
        t##_iter.inc = &deque_inc;                                                                                                         \
        t##_iter.deref = &deque_deref;                                                                                                     \
        t##_iter.dec = &deque_dec;                                                                                                         \
        return t##_iter;                                                                                                                   \
    }                                                                                                                                      \
    bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator begin, Deque_##t##_Iterator end) {                                                \
        return (begin.deque_##t##_index == end.deque_##t##_index);                                                                         \
    }                                                                                                                                      \
    void updateDequeCapacity(Deque_##t *deq) {                                                                                             \
        int f_idx = deq->dq_frnt_idx, index = deq->dq_frnt_idx;                                                                            \
        size_t new_capacity = deq->dq_capacity * 2;                                                                                        \
        auto *new_dq = new t[new_capacity];                                                                                                \
        if (new_dq != nullptr) {                                                                                                           \
            memset(new_dq, 0, new_capacity * sizeof(int));                                                                                 \
            while (deq->dq_frnt_idx != deq->dq_bck_idx) {                                                                                  \
                new_dq[index] = deq->t##_ldata[deq->dq_frnt_idx];                                                                          \
                deq->dq_frnt_idx--;                                                                                                        \
                index--;                                                                                                                   \
                if (deq->dq_frnt_idx < 0) {                                                                                                \
                    deq->dq_frnt_idx += deq->dq_capacity;                                                                                  \
                }                                                                                                                          \
                if (index < 0) {                                                                                                           \
                    index += new_capacity;                                                                                                 \
                }                                                                                                                          \
            }                                                                                                                              \
            new_dq[index] = deq->t##_ldata[deq->dq_frnt_idx];                                                                              \
            auto *temp = deq->t##_ldata;                                                                                                   \
            deq->t##_ldata = nullptr;                                                                                                      \
            deq->t##_ldata = new_dq;                                                                                                       \
            delete[] temp;                                                                                                                 \
            deq->dq_frnt_idx = f_idx;                                                                                                      \
            deq->dq_bck_idx = index;                                                                                                       \
            deq->dq_capacity = new_capacity;                                                                                               \
        }                                                                                                                                  \
    }                                                                                                                                      \
    void deque_push_front(Deque_##t *deq, t new_##t) {                                                                                     \
        int f_idx = deq->dq_frnt_idx;                                                                                                      \
        if (!deq->empty(deq)) {                                                                                                            \
            f_idx = (f_idx + 1) % deq->dq_capacity;                                                                                        \
        }                                                                                                                                  \
        deq->t##_ldata[f_idx] = new_##t;                                                                                                   \
        deq->dq_size++;                                                                                                                    \
        deq->dq_frnt_idx = f_idx;                                                                                                          \
        if (deq->dq_size == deq->dq_capacity) {                                                                                            \
            updateDequeCapacity(deq);                                                                                                      \
        }                                                                                                                                  \
    }                                                                                                                                      \
    void deque_push_back(Deque_##t *deq, t new_##t) {                                                                                      \
        int b_idx = deq->dq_bck_idx;                                                                                                       \
        if (deq->empty(deq)) {                                                                                                             \
            deq->t##_ldata[b_idx] = new_##t;                                                                                               \
            deq->dq_size++;                                                                                                                \
            deq->dq_bck_idx = b_idx;                                                                                                       \
        } else {                                                                                                                           \
            b_idx--;                                                                                                                       \
            if (b_idx < 0) {                                                                                                               \
                b_idx = b_idx + deq->dq_capacity;                                                                                          \
            }                                                                                                                              \
            deq->t##_ldata[b_idx] = new_##t;                                                                                               \
            deq->dq_size++;                                                                                                                \
            deq->dq_bck_idx = b_idx;                                                                                                       \
        }                                                                                                                                  \
        if (deq->dq_size == deq->dq_capacity) {                                                                                            \
            updateDequeCapacity(deq);                                                                                                      \
        }                                                                                                                                  \
    }                                                                                                                                      \
    void deque_pop_front(Deque_##t *deq) {                                                                                                 \
        int f_idx = deq->dq_frnt_idx;                                                                                                      \
        if (!deq->empty(deq)) {                                                                                                            \
            f_idx--;                                                                                                                       \
            if (f_idx < 0) {                                                                                                               \
                f_idx = f_idx + deq->dq_capacity;                                                                                          \
            }                                                                                                                              \
            deq->dq_size--;                                                                                                                \
            deq->dq_frnt_idx = f_idx;                                                                                                      \
        }                                                                                                                                  \
    }                                                                                                                                      \
    void deque_pop_back(Deque_##t *deq) {                                                                                                  \
        int b_idx = deq->dq_bck_idx;                                                                                                       \
        if (!deq->empty(deq)) {                                                                                                            \
            b_idx = (b_idx + 1) % deq->dq_capacity;                                                                                        \
            deq->dq_size--;                                                                                                                \
            deq->dq_bck_idx = b_idx;                                                                                                       \
        }                                                                                                                                  \
    }                                                                                                                                      \
    t& deque_front(Deque_##t *deq) {                                                                                                       \
        return deq->t##_ldata[deq->dq_frnt_idx];                                                                                           \
    }                                                                                                                                      \
    t& deque_back(Deque_##t *deq) {                                                                                                        \
        return deq->t##_ldata[deq->dq_bck_idx];                                                                                            \
    }                                                                                                                                      \
    t& deque_at(Deque_##t *deq, size_t req_index) {                                                                                        \
        int index = deq->dq_frnt_idx - req_index;                                                                                          \
        if (index < 0) {                                                                                                                   \
            index = index + deq->dq_capacity;                                                                                              \
        }                                                                                                                                  \
        return deq->t##_ldata[index];                                                                                                      \
    }                                                                                                                                      \
    void deque_sort(Deque_##t *deq, Deque_##t##_Iterator begin, Deque_##t##_Iterator end) {                                                \
        int i, begin_index = begin.deque_##t##_index;                                                                                      \
        int end_index = end.deque_##t##_index;                                                                                             \
        int sort_list_size = end_index - begin_index;                                                                                      \
        t *sorted_list = new t[sort_list_size];                                                                                            \
        for (i = 0; i < sort_list_size; ++i) {                                                                                             \
            sorted_list[i] = begin.deref(&begin);                                                                                          \
            begin.inc(&begin);                                                                                                             \
        }                                                                                                                                  \
        sort(sorted_list, sorted_list + sort_list_size, deq->comp);                                                                        \
        int b_index = begin_index, index = 0;                                                                                              \
        for (i = 0; i < sort_list_size; ++i) {                                                                                             \
            index = deq->dq_frnt_idx - b_index;                                                                                            \
            if (index < 0) {                                                                                                               \
                index += deq->dq_capacity;                                                                                                 \
            }                                                                                                                              \
            deq->t##_ldata[index] = sorted_list[i];                                                                                        \
            b_index++;                                                                                                                     \
        }                                                                                                                                  \
        delete[] sorted_list;                                                                                                              \
    }                                                                                                                                      \
    void deque_dtor(Deque_##t *deq) {                                                                                                      \
        delete[] deq->t##_ldata;                                                                                                           \
        deq->t##_ldata = nullptr;                                                                                                          \
    }                                                                                                                                      \
    void Deque_##t##_ctor(Deque_##t *deq, bool (*deque_cmp)(const t &o1, const t &o2)) {                                                   \
        deq->t##_ldata = new t[20];                                                                                                        \
        if (deq->t##_ldata != nullptr) {                                                                                                   \
            strcpy(deq->type_name, ("Deque_" #t));                                                                                         \
            deq->dq_frnt_idx = 0;                                                                                                          \
            deq->dq_bck_idx = 0;                                                                                                           \
            deq->dq_capacity = 20;                                                                                                         \
            deq->dq_size = 0;                                                                                                              \
            deq->size = deque_size;                                                                                                        \
            deq->empty = deque_empty;                                                                                                      \
            deq->push_back = &deque_push_back;                                                                                             \
            deq->push_front = &deque_push_front;                                                                                           \
            deq->pop_back = &deque_pop_back;                                                                                               \
            deq->pop_front = &deque_pop_front;                                                                                             \
            deq->front = &deque_front;                                                                                                     \
            deq->back = &deque_back;                                                                                                       \
            deq->at = &deque_at;                                                                                                           \
            deq->begin = &deque_begin;                                                                                                     \
            deq->end = &deque_end;                                                                                                         \
            deq->clear = &deque_clear;                                                                                                     \
            deq->dtor = &deque_dtor;                                                                                                       \
            deq->comp = deque_cmp;                                                                                                         \
            deq->sort = deque_sort;                                                                                                        \
        }                                                                                                                                  \
    }
#endif
