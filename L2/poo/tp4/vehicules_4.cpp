#include <cstdio>

class vehicules_t{
    private:
        float fuel;
        float fuel_cons;
        float fuel_max;
        char* name;
        static float nkm;
    
    public:
        vehicules_t(float fuel, float fuel_cons, float fuel_max, char* name):
            fuel(fuel),
            fuel_cons(fuel_cons),
            fuel_max(fuel_max),
            name(name)
            {}

        float get_fuel() const{
            return this->fuel;
        }

        float get_fuel_cons() const{
            return this->fuel_cons;
        }

        float get_fuel_max() const{
            return this->fuel_max;
        }

        char* get_name() const{
            return this->name;
        }

        static float get_nkm(){
            return nkm;
        }

        bool move(float km = 1){
            float used = (km*get_fuel_cons()) / 100;
            if(km < 0 || get_fuel()-used < 0){
                return false;
            }

            this->fuel -= used;
            nkm += km;
            return true;
        }

        bool refuel(float l){
            if(l + get_fuel() > get_fuel_max()){
                return false;
            }

            this->fuel += l;
            return true;
        }


        virtual void print() const = 0;
};

class car_t: virtual public vehicules_t{
    private:
        bool hand_brake_enabled;
        static float nkm;

    public:
        car_t(float fuel, float fuel_cons, float fuel_max, char* name, bool hand_brake_enabled):
            vehicules_t(fuel, fuel_cons, fuel_max, name),
            hand_brake_enabled(hand_brake_enabled)
            {}
        
        void set_hand_break_enabled(bool hand_brake_enabled){
            this->hand_brake_enabled = hand_brake_enabled;
        }

        bool get_hand_brake_enabled() const{
            return this->hand_brake_enabled;
        }


        static float get_nkm(){
            return nkm;
        }

        bool move(float km = 1){
            if(this->hand_brake_enabled){
                return false;
            }

            if(vehicules_t::move(km)){
                nkm += km;
                return true;
            }
            return false;
        }

        virtual void print() const{
            printf("Car (%s, %.2f/%.2f l, %.2f l/100 km, hand brake: %d)\n", get_name(), get_fuel(), get_fuel_max(), get_fuel_cons(), this->hand_brake_enabled);
        }
};

class boat_t: virtual public vehicules_t{
    private:
        bool anchor_enabled;
        static float nkm;
    
    public:
        boat_t(float fuel, float fuel_cons, float fuel_max, char* name, bool anchor_enabled):
            vehicules_t(fuel, fuel_cons, fuel_max, name),
            anchor_enabled(anchor_enabled)
            {}

        void set_anchor_enabled(bool anchor_enabled){
            this->anchor_enabled = anchor_enabled;
        }

        bool get_anchor_enabled() const{
            return this->anchor_enabled;
        }

        static float get_nkm(){
            return nkm;
        }

        bool move(float km = 1){
            if(this->anchor_enabled){
                return false;
            }

            if(vehicules_t::move(km)){
                nkm += km;
                return true;
            }
            return false;
        }
        
        virtual void print() const{
            printf("Boat (%s, %.2f/%.2f l, %.2f l/100 km, anchor: %d)\n", get_name(), get_fuel(), get_fuel_max(), get_fuel_cons(), this->anchor_enabled);
        }
};

class plane_t: virtual public vehicules_t{
    private:
        bool landing_gear_enabled;
        static float nkm;
    
    public:
        plane_t(float fuel, float fuel_cons, float fuel_max, char* name, bool landing_gear_enabled):
            vehicules_t(fuel, fuel_cons, fuel_max, name),
            landing_gear_enabled(landing_gear_enabled)
            {}

        void set_landing_gear_enabled(bool landing_gear_enabled){
            this->landing_gear_enabled = landing_gear_enabled;
        }

        bool get_landing_gear_enabled() const{
            return this->landing_gear_enabled;
        }

        static float get_nkm(){
            return nkm;
        }

        bool move(float km = 1){
            if(this->landing_gear_enabled){
                return false;
            }

            if(vehicules_t::move(km)){
                nkm += km;
                return true;
            }
            return false;
        }
        
        virtual void print() const{
            printf("Plane (%s, %.2f/%.2f l, %.2f l/100 km, landing gear: %d)\n", get_name(), get_fuel(), get_fuel_max(), get_fuel_cons(), this->landing_gear_enabled);
        }
};

class amphibian_t : public car_t, boat_t{
    private:

    public:
        amphibian_t(float fuel, float fuel_cons, float fuel_max, char* name, bool hand_brake_enabled, bool anchor_enabled):
            vehicules_t(fuel, fuel_cons, fuel_max, name),
            car_t(fuel, fuel_cons, fuel_max, name, hand_brake_enabled),
            boat_t(fuel, fuel_cons, fuel_max, name, anchor_enabled)
            {
                this->set_hand_break_enabled(hand_brake_enabled);
                this->set_anchor_enabled(anchor_enabled);
            }

        bool move(float km = 1){
            if(get_anchor_enabled() || get_hand_brake_enabled()){
                return false;
            }

            if(vehicules_t::move(km)){
                return true;
            }
            return false;
        }

        virtual void print() const{
            printf("Amphibian (%s, %.2f/%.2f l, %.2f 1/100 km, hand brake: %d, anchor: %d)\n", get_name(), get_fuel(), get_fuel_max(), get_fuel_cons(), get_hand_brake_enabled(), get_anchor_enabled());
        }
};

float vehicules_t::nkm = 0;
float car_t::nkm = 0;
float boat_t::nkm = 0;
float plane_t::nkm = 0;

int main(){
    car_t mercedes(1.7, 11, 2.1, (char*)"Mercedes A-Class", false);
    car_t bmw(57.2, 11.3, 65, (char*)"BMW X4", false);
    boat_t zodiac(1.4, 4.7, 1.7, (char*)"Zodiac", false);
    plane_t concorde(99786, 544, 119500, (char*)"Concorde",false);
    amphibian_t amphibian(10.1, 210, 12.9, (char*) "LARC-V", false, false);

    mercedes.print();
    mercedes.move() ? printf("Car moved (%d km).\n", 1) : fprintf(stderr, "Unable to move the car (%d km).\n", 1);
    mercedes.print();
    mercedes.move(100) ? printf("Car moved (%d km).\n", 100) : fprintf(stderr, "Unable to move the car (%d km).\n", 100);
    mercedes.print();

    bmw.print();
    bmw.move() ? printf("Car moved (%d km).\n", 1) : fprintf(stderr, "Unable to move the car (%d km).\n", 1);
    bmw.print();
    bmw.move(100) ? printf("Car moved (%d km).\n", 100) : fprintf(stderr, "Unable to move the car (%d km).\n", 100);
    bmw.print();
    bmw.set_hand_break_enabled(true);
    bmw.print();
    bmw.move(100) ? printf("Car moved (%d km).\n", 100) : fprintf(stderr, "Unable to move the car (%d km).\n", 100);
    bmw.print();

    zodiac.print();
    zodiac.move() ? printf("Boat moved (%d km).\n", 1) : fprintf(stderr, "Unable to move the boat (%d km).\n", 1);
    zodiac.print();
    zodiac.move(100) ? printf("Boat moved (%d km).\n", 100) : fprintf(stderr, "Unable to move the boat (%d km).\n", 100);
    zodiac.print();

    concorde.print();
    concorde.move() ? printf("Plane moved (%d km).\n", 1) : fprintf(stderr, "Unable to move the plane (%d km).\n", 1);
    concorde.print();
    concorde.move(100) ? printf("Plane moved (%d km).\n", 100) : fprintf(stderr, "Unable to move the plane (%d km).\n", 100);
    concorde.print();

    amphibian.print();
    amphibian.move() ? printf("Amphibian moved (%d km).\n", 1) : fprintf(stderr, "Unable to move the Amphibian (%d km).\n", 1);
    amphibian.print();
    amphibian.move(100) ? printf("Amphibian moved (%d km).\n", 100) : fprintf(stderr, "Unable to move the Amphibian (%d km).\n", 100);
    amphibian.print();

    mercedes.refuel(mercedes.get_fuel_max()-mercedes.get_fuel());
    mercedes.print();
    bmw.refuel(bmw.get_fuel_max()-bmw.get_fuel());
    bmw.print();
    zodiac.refuel(zodiac.get_fuel_max()-zodiac.get_fuel());
    zodiac.print();
    concorde.refuel(concorde.get_fuel_max()-concorde.get_fuel());
    concorde.print();
    amphibian.refuel(amphibian.get_fuel_max()-amphibian.get_fuel());
    amphibian.print();


    printf("vehicule_t::get_nkm(): %.2f\n", vehicules_t::get_nkm());
    printf("car_t::get_nkm(): %.2f\n", car_t::get_nkm());
    printf("boat_t::get_nkm(): %.2f\n", boat_t::get_nkm());
    printf("plane_t::get_nkm(): %.2f\n", plane_t::get_nkm());


    return 0;
}