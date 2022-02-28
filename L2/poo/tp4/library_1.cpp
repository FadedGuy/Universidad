#include <cstdio>
#include <vector>

enum day_t{
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

class doc_t{
    private:
        char* name;
        int year;
    public:
        doc_t():
            name(NULL),
            year(0)
            {}

        void set_name(char* name){
            this->name = name;
        }

        void set_year(int year){
            this->year = year;
        }

        char* get_name() const{
            return this->name;
        }

        int get_year() const{
            return this->year;
        }

        virtual void print() const = 0;
};

class audio_doc_t : virtual public doc_t{
    private:
        int duration;
    public:
        audio_doc_t():
            doc_t(),
            duration(0)
            {}

        void set_duration(int duration){
            this->duration = duration;
        }

        int get_duration() const{
            return this->duration;
        }

        virtual void print() const = 0;
};

class textual_doc_t : virtual public doc_t{
    private:

    public:
        textual_doc_t():
            doc_t()
            {}

        virtual void print() const = 0;
};

class video_doc_t : virtual public doc_t{
    private:
        int duration;
        bool color_available;
    public:
        video_doc_t():
            doc_t(),
            duration(0),
            color_available(false)
            {}

        void set_duration(int duration){
            this->duration = duration;
        }

        void set_color_available(bool color_available){
            this->color_available = color_available;
        }
    
        int get_duration() const{
            return this->duration;
        }
    
        bool get_color_available() const{
            return this->color_available;
        }

        virtual void print() const = 0;
};

class audio_tape_t : public audio_doc_t{
    private:

    public:
        audio_tape_t():
            audio_doc_t()
            {}

        void print() const{
            printf("Audio tape (\"%s\", %d, %d s)", get_name(), get_year(), get_duration());
        }
};

class audio_cd_t : public audio_doc_t{
    private:

    public:
        audio_cd_t():
            audio_doc_t()
            {}

        void print() const{
            printf("Audio CD (\"%s\", %d, %d s)", get_name(), get_year(), get_duration());
        }
};

class book_t : public textual_doc_t{
    private:
        std::vector<char*> authors;
        int nauthors;
        char* publisher;
        long isbn;

    public:
        book_t():
            nauthors(0),
            publisher(NULL),
            isbn(0)
            {}

        void set_publisher(char* publisher){
            this->publisher = publisher;
        }

        void set_isbn(long isbn){
            this->isbn = isbn;
        }

        void add_author(char* author){
            this->authors.push_back(author);
            this->nauthors++;
        }

        void print() const{
            printf("Book (\"%s\", (", get_name());
            for(int i = 0; i < this->nauthors; i++){
                i == this->nauthors-1 ? printf("\"%s\"), ", this->authors[i]) : printf("\"%s\", ", this->authors[i]); 
            }
            printf("\"%s\", %d, %ld)", this->publisher, get_year(), this->isbn);
        }
};

class newspaper_t : public textual_doc_t{
    private:
        char* publisher;
        long issn;
    public:
        newspaper_t():
            publisher(NULL),
            issn(0)
            {}

        void set_publisher(char* publisher){
            this->publisher = publisher;
        }

        void set_issn(long issn){
            this->issn = issn;
        }

        void print() const{
            printf("Newspaper (\"%s\", %d, \"%s\", %ld s)", get_name(), get_year(), this->publisher, this->issn);
        }
};

class video_tape_t : public video_doc_t{
    private:

    public:
        video_tape_t():
            video_doc_t()
            {}
        
        void print() const{
            printf("Video tape (\"%s\", %d, %d s, color available: %d)", get_name(), get_year(), get_duration(), get_color_available());
        }
};

class dvd_t : public video_doc_t{
    private:

    public:
        dvd_t():
            video_doc_t()
            {}

        void print() const{
            printf("DVD (\"%s\", %d, %d s, color available: %d)", get_name(), get_year(), get_duration(), get_color_available());
        }
};

class blu_ray_t : public video_doc_t{
    private:

    public:
        blu_ray_t():
            video_doc_t()
            {}

        void print() const{
            printf("Blu-ray (\"%s\", %d, %d s, color available: %d)", get_name(), get_year(), get_duration(), get_color_available());
        }
};

class audio_text_t : public audio_doc_t, video_doc_t{
    private:
    public:
        audio_text_t():
            doc_t(),
            audio_doc_t(),
            video_doc_t()
            {}

        void print() const{
            printf("Audio text (\"%s\", %d, %d s)", get_name(), get_year(), audio_doc_t::get_duration());
        }
};

class library_t{
    private:
        char* name;
        std::vector<day_t> days;
        int ndays;
        std::vector<doc_t *> docs;
        int ndocs;

    public:
        library_t():
            name(NULL),
            ndays(0),
            ndocs(0)
            {}

        void set_name(char* name){
            this->name = name;
        }

        void add_day(day_t day){
            this->days.push_back(day);
            this->ndays++;
        }

        void add_doc(doc_t* doc){
            this->docs.push_back(doc);
            this->ndocs++;
        }

        void print() const{
            char days_str[7][15] = {"monday", "tueday", "wednesday", "thursday", "friday", "saturday", "sunday"};
            
            printf("Library (\"%s\", (", this->name);
            for(int i = 0; i < this->ndays; i++){
                i == this->ndays-1 ? printf("\"%s\"", days_str[this->days[i]]) : printf("\"%s\", ", days_str[this->days[i]]);
            }
            printf("), (");

            for(int i = 0; i < this->ndocs; i++){
                this->docs[i]->print();
                if(i != this->ndocs-1){
                    printf(", ");
                }
            }
            printf(")");
        }
};

int main(){
    book_t b1;
    library_t sciences_lib, novel_lib;

    sciences_lib.set_name((char*) "Sciences Library");
    sciences_lib.add_day(monday);
    sciences_lib.add_day(tuesday);
    sciences_lib.add_day(wednesday);
    sciences_lib.add_day(thursday);

    b1.set_name((char*) "The C++ Programming Language");    
    b1.add_author((char*) "Bjarne Stroustrup");
    b1.set_publisher((char*) "Addison-Wesley");
    b1.set_year(2013);
    b1.set_isbn(9780321563842);
    sciences_lib.add_doc(&b1);

    sciences_lib.print();

    // doc_t b1, b2, b3, b4;
    // library_t sciences_lib, novel_lib;
    
    // sciences_lib.set_name((char*) "Sciences Library");
    // sciences_lib.add_day(monday);
    // sciences_lib.add_day(tuesday);
    // sciences_lib.add_day(wednesday);
    // sciences_lib.add_day(thursday);

    // b1.set_name((char*) "The C++ Programming Language");
    // b1.add_author((char*) "Bjarne Stroustrup");
    // b1.set_publisher((char*) "Addison-Wesley");
    // b1.set_year(2013);
    // b1.set_isbn(9780321563842);
    // sciences_lib.add_doc(b1);

    // b2.set_name((char*) "C++: The Complete Reference");
    // b2.add_author((char*) "Herbert Schildt");
    // b2.set_publisher((char*) "McGraw-Hill");
    // b2.set_year(2003);
    // b2.set_isbn(9780070532465);
    // sciences_lib.add_doc(b2);

    // sciences_lib.print();

    // novel_lib.set_name((char*) "Novel Library");
    // novel_lib.add_day(tuesday);
    // novel_lib.add_day(wednesday);
    // novel_lib.add_day(thursday);
    // novel_lib.add_day(friday);

    // b3.set_name((char*) "Harry Potter and the Philosopher's Stone");
    // b3.add_author((char*) "J. K. Rowling");
    // b3.set_publisher((char*) "Bloomsbury");
    // b3.set_year(1997);
    // b3.set_isbn(9780747532699);
    // novel_lib.add_doc(b3);

    // b4.set_name((char*) "Harry Potter and the Chamber of Secrets");
    // b4.add_author((char*) "J. K. Rowling");
    // b4.set_publisher((char*) "Bloomsbury");
    // b4.set_year(1998);
    // b4.set_isbn(9780747538493);
    // novel_lib.add_doc(b4);

    return 0;
}