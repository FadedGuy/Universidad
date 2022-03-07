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

        void println() const{
            this->print();
            printf("\n");
        }

        virtual void print() const = 0;
};

class audio_doc_t : public doc_t{
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

class textual_doc_t : public doc_t{
    private:

    public:
        textual_doc_t():
            doc_t()
            {}

        virtual void print() const = 0;
};

class video_doc_t : public doc_t{
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
            audio_doc_t(),
            video_doc_t()
            {}

        void print() const{
            printf("Audio text (\"%s\", %d, %d s)", audio_doc_t::get_name(), audio_doc_t::get_year(), audio_doc_t::get_duration());
        }
};

int main(){
    book_t b1, b2, b3, b4;
    audio_tape_t at1;
    audio_cd_t acd1;
    newspaper_t np1;
    video_tape_t vt1;
    dvd_t dvd1;
    blu_ray_t br1;
    audio_text_t atxt1;

    b1.set_name((char*) "The C++ Programming Language");    
    b1.add_author((char*) "Bjarne Stroustrup");
    b1.set_publisher((char*) "Addison-Wesley");
    b1.set_year(2013);
    b1.set_isbn(9780321563842);
    b1.println();

    b2.set_name((char*) "C++: The Complete Reference");    
    b2.add_author((char*) "Herbert Schildt");
    b2.set_publisher((char*) "McGraw-Hill");
    b2.set_year(2003);
    b2.set_isbn(9780070532465);
    b2.println();

    b3.set_name((char*) "Harry Potter and the Philosopher's Stone");
    b3.add_author((char*) "J. K. Rowling");
    b3.set_publisher((char*) "Bloomsbury");
    b3.set_year(1997);
    b3.set_isbn(9780747532699);
    b3.println();

    b4.set_name((char*) "Harry Potter and the Chamber of Secrets");
    b4.add_author((char*) "J. K. Rowling");
    b4.set_publisher((char*) "Bloomsbury");
    b4.set_year(1998);
    b4.set_isbn(9780747538493);
    b4.println();

    at1.set_name((char*) "Killers");
    at1.set_year(1981);
    at1.set_duration(2298);
    at1.println();

    acd1.set_name((char*) "The Book of Souls");
    acd1.set_year(2015);
    acd1.set_duration(5531);
    acd1.println();

    np1.set_name((char*) "The Guardian");
    np1.set_publisher((char*) "Guardian Media Group");
    np1.set_year(1821);
    np1.set_issn(726591);
    np1.println();

    vt1.set_name((char*) "Aladdin");
    vt1.set_year(1992);
    vt1.set_color_available(true);
    vt1.set_duration(5400);
    vt1.println();

    dvd1.set_name((char*) "The Lion King");
    dvd1.set_year(1994);
    dvd1.set_color_available(true);
    dvd1.set_duration(5280);
    dvd1.println();

    br1.set_name((char*) "Zootopia");
    br1.set_year(2016);
    br1.set_color_available(true);
    br1.set_duration(6480);
    br1.println();

    at1.set_name((char*) "Harry Potter and the Philosopher's Stone");
    at1.set_year(1997);
    at1.set_duration(18000);
    at1.println();


    return 0;
}