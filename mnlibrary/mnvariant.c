#include "mnvariant.h"


void int_free(mnptrhld i) {
    free(*i);
    *i = 0;
}

mnvar int_clone(mnvar val) {
    int *i = (int *) malloc(sizeof(int));
    assert(i);
    *i = *(int *) val;
    return i;
}

char int_isequal(mnvar val1, mnvar val2) {
    return *(int *) val1 == *(int *) val2;
}

char int_isgreater(mnvar val1, mnvar val2) {
    return *(int *) val1 > *(int *) val2;
}


void double_free(mnptrhld i) {
    free(*i);
    *i = 0;
}

mnvar double_clone(mnvar val) {
    double *i = (double *) malloc(sizeof(double));
    assert(i);
    *i = *(double *) val;
    return i;
}

char double_isequal(mnvar val1, mnvar val2) {
    return *(double *) val1 == *(double *) val2;
}

char double_isgreater(mnvar val1, mnvar val2) {
    return *(double *) val1 > *(double *) val2;
}

mnvariant *mnvariant_init(mnvariant *var, mntypes data_type, mnvar val,
                          mnfree_fnc free_me) {
    if (!var) {
        var = mnvariant_new();
    }

    var->data_type = data_type;
    var->val = val;
    var->free_me = free_me;
    return var;
}

void mnvariant_clean(mnvariant *var) {
    if (var && var->free_me) {
        var->free_me(&(var->val));
    }
}

mnvariant *mnvariant_new() {
    mnvariant *var = (mnvariant *) malloc(sizeof(mnvariant));
    assert(var);
    var->data_type = -1;
    var->val = 0;
    var->free_me = 0;
    return var;
}

void mnvariant_free(mnvariant **var_hld) {

    mnfree(*var_hld);
    *var_hld = 0;
}

void mnvariant_free_v0(mnvariant *var) {
    mnfree(var);
}

mnvar mnvariant_value(mnvariant *var) {
    return var->val;
}

mnvar mnvariant_set_value(mnvariant *var, mnvar value) {
    mnvar v = 0;
    if (var) {
        v = var->val;
        var->val = value;
    }

    return v;
}

mntypes mnvariant_type(mnvariant *var) {
    return var->data_type;
}

void mnvariant_set_type(mnvariant *var, mntypes data_type) {
    var->data_type = data_type;
}

void mnvariant_clean_free(mnvariant **var_hld) {
    mnvariant_clean(*var_hld);
    mnvariant_free(var_hld);
}

void mnvariant_clean_free_v0(mnvariant *var) {
    mnvariant_clean(var);
    mnvariant_free(&var);
}

mnvariant *mnvariant_clone(mnvariant *var, mnf_var_var clone_val) {
    return mnvariant_init(mnvariant_new(),
                          mnvariant_type(var), clone_val(mnvariant_value(var)),
                          var->free_me);
}

mnvariant *mnvariant_init_int(mnvariant *var, int n) {
    int *i = (int *) malloc(sizeof(int));
    assert(i);
    *i = n;
    return mnvariant_init(var, Int, i, int_free);

}


int mnvariant_int(mnvariant *var) {
    mnassert(var);
    if (var->data_type != Int) {
        mnassert(0);
    }
    return *(int *) var->val;
}

mnvariant *mnvariant_init_double(mnvariant *var, double n) {
    double *i = (double *) malloc(sizeof(double));
    assert(i);
    *i = n;
    return mnvariant_init(var, Double, i, double_free);

}

double mnvariant_double(mnvariant *var) {
    mnassert(var);
    if (var->data_type != Double) {
        mnassert(0);
    }
    return *(double *) var->val;
}

mnvariant *mnvariant_init_cstring(mnvariant *var, char *str) {
    return mnvariant_init(var, CString, str, cstring_free);

}

mnvariant *mnvariant_init_big_int(mnvariant *var, long long int big_int) {
    long long int *i = mnalloc(sizeof(long long int));
    assert(i);
    *i = big_int;
    return mnvariant_init(var, Big_int, i, int_free);
}

long long int mnvariant_big_int(mnvariant *var) {
    return *((long long int *) var->val);
}

mnvariant *mnvariant_init_cstring_cpy(mnvariant *var, char *str) {
    return mnvariant_init_cstring(var, cstring_new_clone(str));
}

char *mnvariant_cstring_ret_ref(mnvariant *var) {
    mnassert(var);
    if (var->data_type != CString) {
        mnassert(0);
    }

    return (char *) var->val;
}

char *mnvariant_to_new_cstring_printable(mnvariant *var) {
    //TODO:test mnvariant_to_new_cstring
    char *str = 0;
    switch (mnvariant_type(var)) {
        case Int:
            str = cstring_new_fill_with_char(' ', INT_PRINT_SIZE);
            char s[25];
            sprintf(s, "%d", mnvariant_int(var));
            cstring_replace_sub_string_at(str, 0, s);
            return str;

        case CString:
            str = cstring_new_fill_with_char(' ', STRING_PRINT_SIZE);
            cstring_replace_sub_string_at(str, 0, mnvariant_cstring_ret_ref(var));
            return str;

        case Double:

            str = cstring_new_fill_with_char(' ', DOUBLE_PRINT_SIZE);
            char s1[50];
            sprintf(s1, "%f", mnvariant_double(var));
            cstring_replace_sub_string_at(str, 0, s1);
            return str;

        default:
            assert(0);


        case Big_int:
            str = cstring_new_fill_with_char(' ', DOUBLE_PRINT_SIZE);
            char s3[200];
            sprintf(s1, "%lld", mnvariant_big_int(var));
            cstring_replace_sub_string_at(str, 0, s1);
            return str;

        case Null:
            return str_cpy("");

    }
}

char *mnvariant_to_new_cstring_out_size(mnvariant *var, size_t out_size) {
    //TODO:test mnvariant_to_new_cstring
    char *str = 0;
    str = cstring_new_fill_with_char(' ', out_size);
    char s[250];
    switch (mnvariant_type(var)) {
        case Int:
            sprintf(s, "%d", mnvariant_int(var));
            cstring_replace_sub_string_at(str, 0, s);
            return str;

        case CString:
            cstring_replace_sub_string_at(str, 0, mnvariant_cstring_ret_ref(var));
            return str;

        case Double:
            sprintf(s, "%f", mnvariant_double(var));
            cstring_replace_sub_string_at(str, 0, s);
            return str;

        default:
            assert(0);


        case Big_int:
            sprintf(s, "%lld", mnvariant_big_int(var));
            cstring_replace_sub_string_at(str, 0, s);
            return str;

        case Null:
            return str_cpy("");

    }
}

char *mnvariant_to_new_cstring(mnvariant *var) {
    char *str = 0;
    char s[500];
    switch (mnvariant_type(var)) {
        case Int:
            sprintf(s, "%d", mnvariant_int(var));
            str = cstring_new_clone(s);
            return str;
        case CString:
            str = cstring_new_clone(mnvariant_cstring_ret_ref(var));
            return str;
        case Double:
            sprintf(s, "%f", mnvariant_double(var));
            str = cstring_new_clone(s);
            return str;
        case Big_int:
            sprintf(s, "%lld", mnvariant_big_int(var));
            str = cstring_new_clone(s);
            return str;

        default:
            assert(0);
        case Null:
            return str_cpy("");

    }
}

mnvariant *mnarray_add_variant(mnarray *arr, mnvariant *var) {
    mnarray_add(arr, var);
    return var;
}

mnvariant *mnarray_mnvaraiant_at(mnarray *arr, size_t ind) {
    return (mnvariant *) mnarray_item_at(arr, ind);
}

mnarray *mnarray_clean_mnvariant(mnarray *arr) {
    return mnarray_clean(arr, (mnf_void_ptrhld) mnvariant_clean_free);
}

size_t mnarray_search_first_mnvariant(mnarray *arr, mnvariant *var_to_search) {
    return mnarray_search_first(arr, var_to_search, (mnf_char_var_var) mnvariant_is_equal);
}

size_t mnarray_search_next_mnvariant(mnarray *arr, mnvariant *var_to_search) {
    return mnarray_search_next(arr, var_to_search, (mnf_char_var_var) mnvariant_is_equal);
}

char mnvariant_is_equal(mnvariant *var1, mnvariant *var2) {
    if (var1->data_type != var2->data_type) {
        return 0;
    }

    switch (var1->data_type) {
        case CString:
            return cstring_is_equal(var1->val, var2->val);

        case Int:
            return mnvariant_int(var1) == mnvariant_int(var2);

        case Double:
            return mnvariant_double(var1) == mnvariant_double(var2);

        default:
            assert(0);

        case Big_int:
            return mnvariant_big_int(var1)== mnvariant_big_int(var2);

        case Null:
            assert(0);

    }
}

mnvariant *mnvariant_clone_v0(mnvariant *var) {
    mnvariant *clone;
    switch (var->data_type) {

        case CString:
            return mnvariant_init_cstring(0, str_cpy(mnvariant_cstring_ret_ref(var)));
        case Double:
            return mnvariant_init_double(0, mnvariant_double(var));
        case Int:
            return mnvariant_init_int(0, mnvariant_int(var));
        case Big_int:
            return mnvariant_init_big_int(0, mnvariant_big_int(var));
        default:
            assert(0);
    }

}

char *mnvariant_cstring_ret_cpy(mnvariant *var) {
    return str_cpy(mnvariant_cstring_ret_ref(var));
}

void mnvariant_printf(mnvariant *var) {
    switch (var->data_type) {
        case CString:
            printf("%s\n", mnvariant_cstring_ret_ref(var));
            break;
        case Double:
            printf("%f\n", mnvariant_double(var));
            break;
        case Int:
            printf("%d\n", mnvariant_int(var));
            break;
        case Big_int:
            printf("%lld\n", mnvariant_big_int(var));
            break;
        default:
            assert(0);
    }
}


mnvariant *mnvariant_init_null() {
    mnvariant * v= mnvariant_init(0,Null,0,mnfree_v0);
    return v;
}

char mnvariant_is_null(mnvariant *var) {
    if (var->data_type==Null) return 1;
    return 0;
}

