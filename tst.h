#ifndef __TST__H_INCLUDED__
#define __TST__H_INCLUDED__

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>

#ifdef __PYTHON__BUILD__
    #include "Python.h"
    #define tst_malloc PyMem_Malloc
    #define tst_realloc PyMem_Realloc
    #define tst_free PyMem_Free
#else
    #define tst_malloc malloc
    #define tst_realloc realloc
    #define tst_free free
#endif

#include "debug.h"

#define UNDEFINED_INDEX -1

template<class S,class T> class tst_node {
public:
    S c;
    T data;
    int next;
    int right;
    int left;
    int height;
    int position;
    int backtrack;
    int backtrack_match_index;
};

template<class S,class T> class action {
public:
    virtual ~action() {}
    virtual void perform(S* key,int remaining_distance,T data)=0;
    virtual T result()=0;
};

template<class S,class T> class filter {
public:
    virtual ~filter() {}
    virtual T perform(S* key,int remaining_distance,T data)=0;
};

template<class S,class T> class serializer {
public:
    virtual ~serializer() {}
    virtual void write(FILE* file,T data)=0;
    virtual T read(FILE* file)=0;
};

template<class S,class T> class tst {
public:
    tst(FILE* file,serializer<S,T>* reader);
    tst(int initial_size,T default_value);
    virtual ~tst() {
        clear_nodes();
    };

    void pack();
    T walk(filter<S,T>* filter,action<S,T>* to_perform);
    T almost(S* string,int string_length,int maximum_distance,filter<S,T>* filter,action<S,T>* to_perform);
    T common_prefix(S* string,filter<S,T>* filter,action<S,T>* to_perform);
    T scan(S* string,action<S,T>* to_perform);
    T scan_with_stop_chars(S* string,S* stop_chars,action<S,T>* to_perform);
    T get(S* string);
    virtual T get_or_build(S* string,filter<S,T>* factory);
    virtual T put(S* string,T data);
    virtual void remove(S* string);
    int get_maximum_key_length();
    size_t bytes_allocated();
    void write(FILE* file,serializer<S,T>* writer);

    void debug_print_root() {
        int next_index=UNDEFINED_INDEX;
        printf("Size: %i (%i bytes), next: %i (%i bytes)\n",size,size*sizeof(tst_node<S,T>),next,next*sizeof(tst_node<S,T>));
        if(root!=UNDEFINED_INDEX) {
            tst_node<S,T>* node=array+root;
            printf("root index: %i, next: %i, c: %c, height: %i, position: %i\n",root,node->next,node->c,node->height,node->position);
            next_index = node->next;
            if(next_index!=UNDEFINED_INDEX) {
                node=array+next_index;
                printf("root->next index: %i, next: %i, c: %c, height: %i, position: %i\n",next_index,node->next,node->c,node->height,node->position);
                next_index = node->next;
                if(next_index!=UNDEFINED_INDEX) {
                    node=array+next_index;
                    printf("root->next->next index: %i, next: %i, c: %c, height: %i, position: %i\n",next_index,node->next,node->c,node->height,node->position);
                }
            }
        }
    }

protected:
    tst_node<S,T>* array;
    T default_value;
    int root,next,size,empty,maximum_key_length;

    tst();
    virtual void read(FILE* file,serializer<S,T>* serializer);

    void walk_recurse(tst_node<S,T>* current_node,S* current_key,int current_key_length,int current_key_limit,filter<S,T>* filter,action<S,T>* to_perform);
    void almost_recurse(tst_node<S,T>* current_node,S* current_key, int current_key_length, S* current_char,int current_index, int real_string_length, int string_length, int remaining_distance,filter<S,T>* filter,action<S,T>* to_perform,int current_key_limit);

    virtual int create_node(tst_node<S,T>** current_node,int current_index);

    virtual int build_node(tst_node<S,T>** current_node,int* current_index,S* current_char,int current_key_length);
    virtual void remove_node(int* current_index,S* current_char,int current_key_length);
    tst_node<S,T>* find_node(int* current_index,int* best_node, S* current_char);

    void compute_backtrack(tst_node<S,T> *current_node,S *start,S *match,S *current_pos);

    void balance_node(tst_node<S,T>** current_node,int* current_index);
    void ll(tst_node<S,T>** current_node,int* current_index);
    void rr(tst_node<S,T>** current_node,int* current_index);
    void lr(tst_node<S,T>** current_node,int* current_index);
    void rl(tst_node<S,T>** current_node,int* current_index);
    int compute_height_and_balance(tst_node<S,T>* current_node);

    virtual void clear_nodes();

    virtual T store_data(tst_node<S,T>* node,T data,int want_old_value) {
        T result=node->data;
        node->data=data;
        return result;
    }
};

template<class S,class T> tst<S,T>::tst(int size,T default_value) {
    this->size=size;
    this->default_value=default_value;
    array=(tst_node<S,T>*)tst_malloc(size*sizeof(tst_node<S,T>));
    next=0;
    empty=UNDEFINED_INDEX;
    root=create_node(&array,0);
    maximum_key_length=0;
}

template<class S,class T> tst<S,T>::tst() {
}

template<class S,class T> tst<S,T>::tst(FILE* file, serializer<S,T>* reader) {
    tst<S,T>::read(file,reader);
}

template<class S,class T> void tst<S,T>::read(FILE* file, serializer<S,T>* reader) {
    fread(&size,sizeof(int),1,file);
    next=size;
    fread(&root,sizeof(int),1,file);
    fread(&maximum_key_length,sizeof(int),1,file);
    int has_data=fgetc(file);
    if(has_data) {
        default_value=reader->read(file);
    }
    else {
        default_value=NULL;
    }
    array=(tst_node<S,T>*)tst_malloc(size*sizeof(tst_node<S,T>));
    memset(array,0,size*sizeof(tst_node<S,T>));
    for(int i=0;i<size;i++) {
        tst_node<S,T>* node=array+i;

        node->c=fgetc(file);
        fread(&(node->left),sizeof(int),1,file);
        fread(&(node->next),sizeof(int),1,file);
        fread(&(node->right),sizeof(int),1,file);
        fread(&(node->height),sizeof(int),1,file);

        has_data=fgetc(file);
        if(has_data) {
            store_data(node,reader->read(file),0);
        }
        else {
            store_data(node,default_value,0);
        }
    }
}

template<class S,class T> void tst<S,T>::write(FILE* file, serializer<S,T>* writer) {
    fwrite(&next,sizeof(int),1,file);
    fwrite(&root,sizeof(int),1,file);
    fwrite(&maximum_key_length,sizeof(int),1,file);
    if(default_value) {
        putc('\1',file);
        writer->write(file,default_value);
    }
    else {
        putc('\0',file);
    }
    for(int i=0;i<next;i++) {
        tst_node<S,T>* node=array+i;
        fputc(node->c,file);
        fwrite(&(node->left),sizeof(int),1,file);
        fwrite(&(node->next),sizeof(int),1,file);
        fwrite(&(node->right),sizeof(int),1,file);
        fwrite(&(node->height),sizeof(int),1,file);
        T data=node->data;
        if(data!=default_value) {
            fputc('\1',file);
            writer->write(file,data);
        }
        else {
            fputc('\0',file);
        }
    }
}

template<class S,class T> void tst<S,T>::clear_nodes() {
    if(array) {
        for(int i=0;i<next;i++) {
            store_data(array+i,(T)NULL,0);
        }
        tst_free(array);
        array=NULL;
    }
}

template<class S,class T> void tst<S,T>::pack() {
    if(next<size) {
        size=next;
        array=(tst_node<S,T>*)tst_realloc(array,size*sizeof(tst_node<S,T>));
    }
}

template<class S,class T> T tst<S,T>::get(S* string) {
    int current_index=root,best_node=UNDEFINED_INDEX;
    tst_node<S,T>* current_node=find_node(&current_index,&best_node,string);
    if(current_node) {
        return current_node->data;
    }
    else {
        return default_value;
    }
}

template<class S,class T> T tst<S,T>::put(S* string,T data) {
    tst_node<S,T>* current_node=array+root;
    int node_index=build_node(&current_node,&root,string,0);
    current_node=array+node_index;
    return store_data(current_node,data,1);
}

template<class S,class T> void tst<S,T>::remove(S* string) {
    remove_node(&root,string,0);
    if(root==UNDEFINED_INDEX) {
        root=create_node(&array,0);
    }
}

template<class S,class T> T tst<S,T>::get_or_build(S* string,filter<S,T>* factory) {
    tst_node<S,T>* current_node=array+root;
    int node_index=build_node(&current_node,&root,string,0);
    current_node=array+node_index;
    T data=factory->perform(string,0,current_node->data);
    if(data!=current_node->data) {
        store_data(current_node,data,0);
    }
    return data;
}

template<class S,class T> T tst<S,T>::almost(S* string, int string_length, int maximum_distance,filter<S,T>* filter,action<S,T>* to_perform) {
    S* current_key=(S*)tst_malloc((string_length+maximum_distance+1)*sizeof(S));
    *current_key='\0';
    almost_recurse(array+root,current_key,0,string,0,string_length,string_length,maximum_distance,filter,to_perform,string_length+maximum_distance);
    tst_free(current_key);
    return to_perform->result();
}

template<class S,class T> T tst<S,T>::walk(filter<S,T>* filter,action<S,T>* to_perform) {
    S* key=(S*)tst_malloc((maximum_key_length+2)*sizeof(S));
    *key='\0';
    walk_recurse(array+root,key,0,maximum_key_length+1,filter,to_perform);
    tst_free(key);
    return to_perform->result();
}

template<class S,class T> void tst<S,T>::walk_recurse(tst_node<S,T>* current_node,S* current_key,int current_key_length,int current_key_limit,filter<S,T>* filter,action<S,T>* to_perform) {
    int other_index;

    other_index=current_node->left;
    if(other_index!=UNDEFINED_INDEX) {
        walk_recurse(array+other_index,current_key,current_key_length,current_key_limit,filter,to_perform);
    }

    T data = current_node->data;
    if(data!=default_value && filter) {
        data = filter->perform(current_key,0,data);
    }
    if(data!=default_value && to_perform) {
        assert(current_key[current_key_length]=='\0');
        assert(current_key_length < current_key_limit);
        current_key[current_key_length]=current_node->c;
        current_key[current_key_length+1]='\0';
        to_perform->perform(current_key,0,data);
        current_key[current_key_length]='\0';
    }

    other_index=current_node->next;
    if(other_index!=UNDEFINED_INDEX) {
        assert(current_key[current_key_length]=='\0');
        assert(current_key_length < current_key_limit);
        current_key[current_key_length]=current_node->c;
        current_key[current_key_length+1]='\0';
        walk_recurse(array+other_index,current_key,current_key_length+1,current_key_limit,filter,to_perform);
        current_key[current_key_length]='\0';
    }

    other_index=current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        walk_recurse(array+other_index,current_key,current_key_length,current_key_limit,filter,to_perform);
    }
}

template<class S,class T> void tst<S,T>::almost_recurse(tst_node<S,T>* current_node,S* current_key,int current_key_length,S* string, int current_index, int real_string_length, int string_length, int remaining_distance,filter<S,T>* filter, action<S,T>* to_perform,int current_key_limit) {
    int other_index;
    int diff,diff2;

    other_index=current_node->left;
    if (other_index!=UNDEFINED_INDEX) {
        almost_recurse(array+other_index,current_key,current_key_length,string,current_index,real_string_length,string_length,remaining_distance,filter,to_perform,current_key_limit);
    }

    diff=0;
    if(current_index<real_string_length) {
        if((string[current_index]-current_node->c)!=0) {
            diff=1;
        }
    }
    else {
        diff=1;
    }

    T data = current_node->data;
    if(data!=default_value && filter) {
        data = filter->perform(current_key,0,data);
    }
    if(data!=default_value && to_perform) {
        diff2=(remaining_distance-abs(current_key_length+1-string_length))-diff;
        if(diff2>=0) {
            assert(current_key[current_key_length]=='\0');
            assert(current_key_length < current_key_limit);
            current_key[current_key_length]=current_node->c;
            current_key[current_key_length+1]='\0';
            to_perform->perform(current_key,diff2,data);
            current_key[current_key_length]='\0';
        }
    }

    other_index=current_node->next;
    if (other_index!=UNDEFINED_INDEX) {
        diff2 = remaining_distance - diff;
        if (diff2>=0) {
            assert(current_key[current_key_length]=='\0');
            assert(current_key_length < current_key_limit);
            current_key[current_key_length]=current_node->c;
            current_key[current_key_length+1]='\0';
            almost_recurse(array+other_index,current_key,current_key_length+1,string,current_index+1,real_string_length,string_length,diff2,filter,to_perform,current_key_limit);
            current_key[current_key_length]='\0';
        }
    }

    if(current_index<string_length && remaining_distance>0) {
        assert(current_key[current_key_length]=='\0');
        almost_recurse(current_node,current_key,current_key_length,string,current_index+1,real_string_length,string_length-1,remaining_distance-1,filter,to_perform,current_key_limit);
    }

    if(other_index!=UNDEFINED_INDEX && remaining_distance>0) {
        assert(current_key[current_key_length]=='\0');
        assert(current_key_length < current_key_limit);
        current_key[current_key_length]=current_node->c;
        current_key[current_key_length+1]='\0';
        almost_recurse(array+other_index,current_key,current_key_length+1,string,current_index,real_string_length,string_length+1,remaining_distance-1,filter,to_perform,current_key_limit);
        current_key[current_key_length]='\0';
    }

    other_index = current_node->right;
    if(other_index!=UNDEFINED_INDEX) {
        assert(current_key[current_key_length]=='\0');
        almost_recurse(array+other_index,current_key,current_key_length,string,current_index,real_string_length,string_length,remaining_distance,filter,to_perform,current_key_limit);
    }
}

template<class S,class T> T tst<S,T>::common_prefix(S* string,filter<S,T>* filter,action<S,T>* to_perform) {
    S* current_key=(S*)tst_malloc((maximum_key_length+2)*sizeof(S));
    int current_key_length=0;
    *current_key='\0';

    T biggest=default_value;
    int current_index=root;
    tst_node<S,T>* current_node;
    int diff;
    S c;

    while(c=*(string++)) {
        assert(current_key_length<=maximum_key_length);
        current_key[current_key_length]=c;
        current_key[current_key_length+1]='\0';
        current_key_length++;
        while(current_index!=UNDEFINED_INDEX) {
            current_node=array+current_index;
            diff=c-current_node->c;
            if(diff==0) {
                if(current_node->data!=default_value) {
                    biggest=current_node->data;
                    if(filter) {
                        biggest=filter->perform(current_key,0,biggest);
                    }
                }
                if(*string) {
                    current_index=current_node->next;
                    break;
                }
                else {
                    if(biggest!=default_value && to_perform) {
                        to_perform->perform(current_key,0,biggest);
                    }
                    current_index=current_node->next;
                    if(current_index!=UNDEFINED_INDEX) {
                        walk_recurse(array+current_index,current_key,current_key_length,maximum_key_length+2,filter,to_perform);
                    }
                    tst_free(current_key);
                    return to_perform->result();
                }
            }
            else if(diff>0) {
                current_index=current_node->right;
            }
            else {
                current_index=current_node->left;
            }
        }
        if(current_index==UNDEFINED_INDEX) {
            break;
        }
    }

    if(biggest!=default_value && to_perform) {
        to_perform->perform(current_key,0,biggest);
    }
    tst_free(current_key);
    return to_perform->result();
}

template<class S,class T> int tst<S,T>::create_node(tst_node<S,T>** current_node,int current_index) {
    int id;
    tst_node<S,T>* new_node;

    if(next==size) {
        size+=(size>>1);
        array=(tst_node<S,T>*)tst_realloc(array,size*sizeof(tst_node<S,T>));
        *current_node = array+current_index;
    }

    if(empty!=UNDEFINED_INDEX) {
        // si on a un noeud vide on l'utilise.
        id=empty;
        // on passe au noeud vide suivant.
        empty = (array+empty)->next;
    }
    else {
        id=next++;
    }

    new_node=array+id;
    new_node->c=0;
    new_node->next=UNDEFINED_INDEX;
    new_node->right=UNDEFINED_INDEX;
    new_node->left=UNDEFINED_INDEX;
    new_node->height=0;
    new_node->data=(T)NULL;
    new_node->position=-1;
    new_node->backtrack=UNDEFINED_INDEX;
    new_node->backtrack_match_index=UNDEFINED_INDEX;
    store_data(new_node,default_value,0);

    return id;
}

template<class S,class T> int tst<S,T>::build_node(tst_node<S,T>** current_node,int* current_index,S* current_char,int current_key_length) {
    int diff,result,next_index;

    if((*current_node)->c==0) {
        (*current_node)->c=(*current_char);
        (*current_node)->position=current_key_length;
        diff=0;
    }
    else {
        diff=(*current_char)-((*current_node)->c);
    }

    if(diff==0) {
        current_char++;
        current_key_length++;
        if(*current_char) {
            if(current_key_length>maximum_key_length) {
                maximum_key_length=current_key_length;
            }
            next_index = (*current_node)->next;
            if(next_index==UNDEFINED_INDEX) {
                /* attention cela doit FORCEMENT se faire en deux ligne
                car current_node peut être modifié par tst_create_node. */
                next_index=create_node(current_node,*current_index);
                (*current_node)->next=next_index;
            }
            *current_node = array + next_index;
            result=build_node(current_node,&next_index,current_char,current_key_length);
            *current_node = array + *current_index;
            (*current_node)->next=next_index;
            balance_node(current_node,current_index); // XXX est-ce vraiment utile ?
            return result;
        }
        else {
            return *current_index;
        }
    }
    else if(diff>0) {
        next_index = (*current_node)->right;
        if(next_index==UNDEFINED_INDEX) {
            next_index=create_node(current_node,*current_index);
            (*current_node)->right=next_index;
        }
        *current_node = array + next_index;
        result=build_node(current_node,&next_index,current_char,current_key_length);
        *current_node = array+*current_index;
        (*current_node)->right=next_index;
        balance_node(current_node,current_index);
        return result;
    }
    else {
        next_index = (*current_node)->left;
        if(next_index==UNDEFINED_INDEX) {
            next_index=create_node(current_node,*current_index);
            (*current_node)->left=next_index;
        }
        *current_node = array + next_index;
        result=build_node(current_node,&next_index,current_char,current_key_length);
        *current_node = array+*current_index;
        (*current_node)->left=next_index;
        balance_node(current_node,current_index);
        return result;
    }
}

template<class S,class T> void tst<S,T>::remove_node(int* current_index,S* current_char,int current_key_length) {
    tst_node<S,T>* current_node = array + *current_index;
    int diff,*next_index;

    if(current_node->c==0) {
        return;
    }
    else {
        diff=(*current_char)-(current_node->c);
    }

    if(diff==0) {
        current_char++;
        current_key_length++;
        if(*current_char) {
            if(current_key_length>maximum_key_length) {
                maximum_key_length=current_key_length;
            }
            next_index = &(current_node->next);
            if(*next_index!=UNDEFINED_INDEX) {
                remove_node(next_index,current_char,current_key_length);
            }
        }
        else {
            store_data(current_node,default_value,0);
        }
    }
    else if(diff>0) {
        next_index = &(current_node->right);
        if(*next_index!=UNDEFINED_INDEX) {
            remove_node(next_index,current_char,current_key_length);
        }
    }
    else {
        next_index = &(current_node->left);
        if(*next_index!=UNDEFINED_INDEX) {
            remove_node(next_index,current_char,current_key_length);
        }
    }

    current_node=array+*current_index;

    if(   current_node->data==default_value
        && current_node->next==UNDEFINED_INDEX
        && current_node->right==UNDEFINED_INDEX
        && current_node->left==UNDEFINED_INDEX) {
            // on ajoute le noeud à la liste des noeuds vides
            current_node->next=empty;
            empty = *current_index;
            *current_index=UNDEFINED_INDEX;
        }
    else {
        balance_node(&current_node,current_index);
    }
}

template<class S,class T> tst_node<S,T>* tst<S,T>::find_node(int* current_index,int* best_node,S* current_char) {
    tst_node<S,T>* _array=array;
    tst_node<S,T>* current_node;
    int diff;

    while(*current_index!=UNDEFINED_INDEX) {
        current_node=_array+*current_index;

        if(current_node->c==0) {
            *current_index=UNDEFINED_INDEX;
            return NULL;
        }
        else {
            diff=(*current_char)-(current_node->c);
        }

        if(diff==0) {
            if(current_node->data!=default_value) {
                *best_node=*current_index;
            }

            current_char++;
            if(*current_char) {
                *current_index = current_node->next;
            }
            else {
                return current_node;
            }
        }
        else if(diff>0) {
            *current_index=current_node->right;
        }
        else {
            *current_index=current_node->left;
        }
    }

    return NULL;
}

template<class S,class T> void tst<S,T>::compute_backtrack(tst_node<S,T> *current_node,S *start, S *match,S *current_pos) {
    if(current_node->backtrack==UNDEFINED_INDEX) {
        S temp_char=*match;
        *match=0;
/*
        printf("find backtrack for \"%s|",start);
*/
        *match=temp_char;
        temp_char=*current_pos;
        *current_pos=0;
/*
        printf("%s\"",match);        
*/
        S* forward_pos=match;
        while(forward_pos<current_pos) {
            current_node->backtrack=root;
            current_node->backtrack_match_index=UNDEFINED_INDEX;
            find_node(&(current_node->backtrack),&(current_node->backtrack_match_index),forward_pos);
            if(current_node->backtrack==UNDEFINED_INDEX) {
                forward_pos++;
            }
            else {
                current_node->backtrack=(array+current_node->backtrack)->next;

/*              
                printf(" => \"%s\"(%i)",forward_pos,current_node->backtrack);
                if(current_node->backtrack_match_index!=UNDEFINED_INDEX) {
                    S* best_match_end=forward_pos+(array+current_node->backtrack_match_index)->position+1;
                    S temp_char2=*best_match_end;
                    *best_match_end=0;
                    printf(" with best match \"%s\"\n",forward_pos);
                    *best_match_end=temp_char2;
                }
                else {
                    printf(" with no best match\n");
                }
*/
                break;
            }
        }
        if(current_node->backtrack==UNDEFINED_INDEX) {
/*
            printf(" => nothing !\n");
*/
            current_node->backtrack=root;
            current_node->backtrack_match_index=UNDEFINED_INDEX;
        }
        *current_pos=temp_char;
    }
}

template<class S,class T> T tst<S,T>::scan(S* string,action<S,T>* to_perform) {
/*
    printf("\n--------scan \"%s\"\n",string);
*/
    tst_node<S,T> *current_node=NULL;

    S current_char;
    S temp_char;

    S *current_pos=string;
    int current_index=root;
    S *non_match_start=string;

    int current_match_index=UNDEFINED_INDEX;
    S *current_match_start=NULL;

    current_char=*current_pos;
    current_node=array+current_index;
    while(1) {
        current_node=array+current_index;
/*
        printf("%3i:%3i: %c %c",current_pos-string,current_index,current_node->c,current_char);
*/
        if(current_char) {
            int diff=current_char-current_node->c;
            if(diff>0) {
/*
                printf(" R");
*/
                current_index=current_node->right;
            }
            else if(diff<0) {
/*
                printf(" L");
*/
                current_index=current_node->left;
            }
            else {
                // ok, le caractère courant est accepté
                if(current_match_start==NULL) {
                    current_match_start=current_pos;
                }
                if(current_node->data!=default_value) {
                    // définition du match
                    current_match_index=current_index;
                }
                current_pos++;
                if(*current_pos) {
                    current_index=current_node->next;
                }
                else {
                    current_index=UNDEFINED_INDEX;
                }
/*
                printf(" ok %3i",current_index);            
*/
            }
        }
        else {
            current_index=UNDEFINED_INDEX;
        }

        if(current_index==UNDEFINED_INDEX) {
/*
            printf(" KO\n");
*/

            // Le caractère courant n'est pas accepté
            if(current_match_index!=UNDEFINED_INDEX) {
                tst_node<S,T> *match_node;
                S* current_match_end;

                // envoi de ce qui précède le match
                if(current_match_start>non_match_start) {
                    temp_char=*current_match_start;
                    *current_match_start=0;
/*
                    printf("-> \"%s\"\n",non_match_start);
*/
                    to_perform->perform(non_match_start,(int)(non_match_start-current_match_start),default_value);
                    *current_match_start=temp_char;
                }

                // envoi du match
                match_node=array+current_match_index;
                current_match_end=current_match_start+match_node->position+1;
                temp_char=*current_match_end;
                *current_match_end=0;
/*
                printf("-> \"%s\"\n",current_match_start);
*/
                to_perform->perform(current_match_start,match_node->position+1,match_node->data);
                *current_match_end=temp_char;
                non_match_start=current_match_end;

                // annulation du match
                current_match_index=UNDEFINED_INDEX;

                // backtrack correct !
                compute_backtrack(current_node,current_match_start,current_match_end,current_pos);
                current_index = current_node->backtrack;
                current_match_index=current_node->backtrack_match_index;

                if(current_index==root) {
                    // quand on a un retour à la racine, on n'a aucun match en cours
                    current_match_start=NULL;
                }
                else {
                    // sinon c'est qu'un match est en cours, on va recalculer son point de démarrage
                    // grâce à la position du noeud
                    current_match_start=current_pos-(array+current_index)->position;

/*
                    // DEBUG
                    temp_char=*current_pos;
                    *current_pos=0;
                    printf("Restarting at \"%s|%c\" with state %i\n",current_match_start,temp_char,current_index);
                    *current_pos=temp_char;
                    // END DEBUG
*/
                }
            }
            else if(current_match_start!=NULL) {
                // backtrack correct !

                // on commence par calculer où l'on va aller
                compute_backtrack(current_node,current_match_start,current_match_start+1,current_pos);
                current_index = current_node->backtrack;
                current_match_index=current_node->backtrack_match_index;

                if(current_index==root) {
                    // quand on a un retour à la racine, on n'a aucun match en cours
                    current_match_start=NULL;
                }
                else {
                    // sinon c'est qu'un match est en cours, on va recalculer son point de démarrage
                    // grâce à la position du noeud
                    current_match_start=current_pos-(array+current_index)->position;

/*
                    // DEBUG
                    temp_char=*current_pos;
                    *current_pos=0;
                    printf("Restarting at \"%s|%c\" with state %i\n",current_match_start,temp_char,current_index);
                    *current_pos=temp_char;
                    // END DEBUG
*/
                }
            }
            else {
                if(current_char) {
                    current_pos++;
                    current_index = root;
                    // On annule le match
                    current_match_start=NULL;
                }
                else {
                    break;
                }
            }
        }
/*
        else {
            printf("\n");
        }
*/

        current_char=*current_pos;
    }

    if(current_pos>non_match_start) {
        temp_char=*current_pos;
        *current_pos=0;
/*
        printf("-> \"%s\"\n",non_match_start);
*/
        to_perform->perform(non_match_start,(int)(non_match_start-current_pos),default_value);
        *current_pos=temp_char;
    }

    return to_perform->result();
}

template<class S> int is_in(S c,S* stop_chars) {
    do {
        if(c==*stop_chars) {
            return 1;
        }
    } while(*(stop_chars++));
    return 0;
}

template<class S,class T> T tst<S,T>::scan_with_stop_chars(S* string,S* stop_chars,action<S,T>* to_perform) {
/*
    printf("\n--------scan_with_stop_chars\"%s\"\n",string);
*/
    tst_node<S,T> *current_node=NULL;

    S current_char;
    S temp_char;

    S *current_pos=string;
    int current_index=root;
    S *non_match_start=string;

    int current_match_index=UNDEFINED_INDEX;
    S *current_match_start=NULL;

    current_char=*current_pos;
    current_node=array+current_index;
    while(1) {
        current_node=array+current_index;
/*
        printf("%3i:%3i: %c %c",current_pos-string,current_index,current_node->c,current_char);
*/
        if(current_char) {
            int diff=current_char-current_node->c;
            if(diff>0) {
/*
                printf(" R");
*/
                current_index=current_node->right;
            }
            else if(diff<0) {
/*
                printf(" L");
*/
                current_index=current_node->left;
            }
            else {
                // ok, le caractère courant est accepté
                if(current_match_start==NULL) {
                    if(current_pos==string || is_in(*(current_pos-1),stop_chars)) {
                        current_match_start=current_pos;
                    }
                    else {
                        current_match_start=NULL;
                        current_pos++;
                    }
                }
                if(current_match_start) {
                    if(current_node->data!=default_value && (*(current_pos+1)==0 || is_in(*(current_pos+1),stop_chars))) {
                        // définition du match
                        current_match_index=current_index;
                    }
                    current_pos++;
                    if(*current_pos) {
                        current_index=current_node->next;
                    }
                    else {
                        current_index=UNDEFINED_INDEX;
                    }
/*
                    printf(" ok %3i",current_index);            
*/
                }
            }
        }
        else {
            current_index=UNDEFINED_INDEX;
        }

        if(current_index==UNDEFINED_INDEX) {
/*
            printf(" KO\n");
*/

            // Le caractère courant n'est pas accepté
            if(current_match_index!=UNDEFINED_INDEX) {
                tst_node<S,T> *match_node;
                S* current_match_end;

                // envoi de ce qui précède le match
                if(current_match_start>non_match_start) {
                    temp_char=*current_match_start;
                    *current_match_start=0;
/*
                    printf("-> \"%s\"\n",non_match_start);
*/
                    to_perform->perform(non_match_start,(int)(non_match_start-current_match_start),default_value);
                    *current_match_start=temp_char;
                }

                // envoi du match
                match_node=array+current_match_index;
                current_match_end=current_match_start+match_node->position+1;
                temp_char=*current_match_end;
                *current_match_end=0;
/*
                printf("-> \"%s\"\n",current_match_start);
*/
                to_perform->perform(current_match_start,match_node->position+1,match_node->data);
                *current_match_end=temp_char;
                non_match_start=current_match_end;

                // annulation du match
                current_match_index=UNDEFINED_INDEX;

                // backtrack de naze parce qu'on ne peut pas utiliser
                // les infos de backtrack à cause des séparateurs.
                current_pos=non_match_start;
                current_index = root;
                current_match_index=UNDEFINED_INDEX;
                current_match_start=NULL;
            }
            else if(current_match_start!=NULL) {
                // backtrack de naze parce qu'on ne peut pas utiliser
                // les infos de backtrack à cause des séparateurs.
                current_pos=current_match_start+1;
                current_index = root;
                current_match_index=UNDEFINED_INDEX;
                current_match_start=NULL;
            }
            else {
                if(current_char) {
                    current_pos++;
                    current_index = root;
                    // On annule le match
                    current_match_start=NULL;
                }
                else {
                    break;
                }
            }
        }
/*
        else {
            printf("\n");
        }
*/

        current_char=*current_pos;
    }

    if(current_pos>non_match_start) {
        temp_char=*current_pos;
        *current_pos=0;
/*
        printf("-> \"%s\"\n",non_match_start);
*/
        to_perform->perform(non_match_start,(int)(non_match_start-current_pos),default_value);
        *current_pos=temp_char;
    }

    return to_perform->result();
}


template<class S,class T> void tst<S,T>::balance_node(tst_node<S,T>** current_node,int* current_index) {
    int current_balance;
    current_balance=compute_height_and_balance(*current_node);
    if(current_balance>1) {
        current_balance=compute_height_and_balance(array+(*current_node)->right);
        if(current_balance>0) {
            rr(current_node,current_index);
        }
        else {
            rl(current_node,current_index);
        }
    }
    else if(current_balance<-1) {
        current_balance=compute_height_and_balance(array+(*current_node)->left);
        if(current_balance<0) {
            ll(current_node,current_index);
        }
        else {
            lr(current_node,current_index);
        }
    }
}

template<class S,class T> void tst<S,T>::ll(tst_node<S,T>** current_node,int* current_index) {
    int left_index=(*current_node)->left;
    tst_node<S,T>* left_node=array+left_index;
    int left_right_index=left_node->right;
    (*current_node)->left=left_right_index;
    compute_height_and_balance(*current_node);
    left_node->right=*current_index;
    compute_height_and_balance(left_node);
    *current_index=left_index;
    *current_node=array+left_index;
}

template<class S,class T> void tst<S,T>::rr(tst_node<S,T>** current_node,int* current_index) {
    int right_index=(*current_node)->right;
    tst_node<S,T>* right_node=array+right_index;
    int right_left_index=right_node->left;
    (*current_node)->right=right_left_index;
    compute_height_and_balance(*current_node);
    right_node->left=*current_index;
    compute_height_and_balance(right_node);
    *current_index=right_index;
    *current_node=array+right_index;
}

template<class S,class T> void tst<S,T>::lr(tst_node<S,T>** current_node,int* current_index) {
    int* left_index=&((*current_node)->left);
    tst_node<S,T>* left_node=array+*left_index;
    rr(&left_node,left_index);
    ll(current_node,current_index);
}

template<class S,class T> void tst<S,T>::rl(tst_node<S,T>** current_node,int* current_index) {
    int* right_index=&((*current_node)->right);
    tst_node<S,T>* right_node=array+*right_index;
    ll(&right_node,right_index);
    rr(current_node,current_index);
}

template<class S,class T> int tst<S,T>::compute_height_and_balance(tst_node<S,T>* current_node) {
    int left = current_node->left;
    int right = current_node->right;
    int left_height,right_height,result;
    tst_node<S,T>* left_node;
    tst_node<S,T>* right_node;

    if(right!=UNDEFINED_INDEX) {
        right_node=array+right;
        right_height=right_node->height;
        if(left!=UNDEFINED_INDEX) {
            left_node=array+left;
            left_height=left_node->height;
            result=right_height-left_height;
            if(left_height>right_height) {
                right_height=left_height;
            }
            current_node->height=right_height+1;
            return result;
        }
        else {
            current_node->height=right_height+1;
            return right_height;
        }
    }
    else {
        if(left!=UNDEFINED_INDEX) {
            left_node=array+left;
            left_height=left_node->height;
            current_node->height=left_height+1;
            return -left_height;
        }
        else {
            current_node->height=0;
            return 0;
        }
    }
}

template<class S,class T> size_t tst<S,T>::bytes_allocated() {
    return sizeof(tst)+size*sizeof(tst_node<S,T>);
}

template<class S,class T> int tst<S,T>::get_maximum_key_length() {
    return maximum_key_length;
}

#endif
