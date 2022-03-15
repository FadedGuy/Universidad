#include <iostream>
#include <sstream>
#include <string>

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

class car_t: public vehicules_t{
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

        std::string to_str() const{
            std::ostringstream oss; 
            oss << "Car (" << get_name() << ", " << get_fuel() << "/" << get_fuel_max() << "l, " << get_fuel_cons() << " l/100km, hand brake: " << this->hand_brake_enabled << ")\n";
            return oss.str();
        }

        virtual void print() const{
            std::cout << this->to_str();
        }
};

class boat_t: public vehicules_t{
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
        
        std::string to_str() const{
            std::ostringstream oss; 
            oss << "Boat (" << get_name() << ", " << get_fuel() << "/" << get_fuel_max() << "l, " << get_fuel_cons() << " l/100km, anchor: " << this->anchor_enabled << ")\n";
            return oss.str();
        }

        virtual void print() const{
            std::cout << this->to_str();
        }
};

class plane_t: public vehicules_t{
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

        std::string to_str() const{
            std::ostringstream oss; 
            oss << "Plane (" << get_name() << ", " << get_fuel() << "/" << get_fuel_max() << "l, " << get_fuel_cons() << " l/100km, landing gear: " << this->landing_gear_enabled << ")\n";
            return oss.str();
        }

        virtual void print() const{
            std::cout << this->to_str();
        }
};

float vehicules_t::nkm = 0;
float car_t::nkm = 0;
float boat_t::nkm = 0;
float plane_t::nkm = 0;

std::ostream &operator<<(std::ostream &os, const car_t &car){
    os << car.to_str();
    return os;
}

std::ostream &operator<<(std::ostream &os, const boat_t &boat){
    os << boat.to_str();
    return os;
}

std::ostream &operator<<(std::ostream &os, const plane_t &plane){
    os << plane.to_str();
    return os;
}

int main(){
    car_t mercedes(1.7, 11, 2.1, (char*)"Mercedes A-Class", false);
    car_t bmw(57.2, 11.3, 65, (char*)"BMW X4", false);
    boat_t zodiac(1.4, 4.7, 1.7, (char*)"Zodiac", false);
    plane_t concorde(99786, 544, 119500, (char*)"Concorde",false);

    std::cout << mercedes;
    if(mercedes.move()){
        std::cout << "Car moved (" << 1 << " km)\n";
    }else{
        std::cerr << "Unable to move the car " << 1 << " km).\n";
    }
    std::cout << mercedes;
    if(mercedes.move(100)){
        std::cout << "Car moved (" << 100 << " km)\n";
    }else{
        std::cerr << "Unable to move the car " << 100 << " km).\n";
    }
    std::cout << mercedes;


    std::cout << bmw;
    if(bmw.move()){
        std::cout << "Car moved (" << 1 << " km)\n";
    }else{
        std::cerr << "Unable to move the car " << 1 << " km).\n";
    }
    std::cout << bmw;
    if(bmw.move(100)){
        std::cout << "Car moved (" << 100 << " km)\n";
    }else{
        std::cerr << "Unable to move the car " << 100 << " km).\n";
    }
    std::cout << bmw;
    bmw.set_hand_break_enabled(true);
    std::cout << bmw;
    if(bmw.move(100)){
        std::cout << "Car moved (" << 100 << " km)\n";
    }else{
        std::cerr << "Unable to move the car " << 100 << " km).\n";
    }
    std::cout << bmw;


    std::cout << zodiac;
    if(zodiac.move()){
        std::cout << "Boat moved (" << 1 << " km)\n";
    }else{
        std::cerr << "Unable to move the boat " << 1 << " km).\n";
    }
    std::cout << zodiac;
    if(zodiac.move(100)){
        std::cout << "Boat moved (" << 100 << " km)\n";
    }else{
        std::cerr << "Unable to move the boat " << 100 << " km).\n";
    }
    std::cout << zodiac;

    std::cout << concorde;
    if(concorde.move()){
        std::cout << "Plane moved (" << 1 << " km)\n";
    }else{
        std::cerr << "Unable to move the plane " << 1 << " km).\n";
    }
    std::cout << concorde;
    if(concorde.move(100)){
        std::cout << "Plane moved (" << 100 << " km)\n";
    }else{
        std::cerr << "Unable to move the plane " << 100 << " km).\n";
    }
    std::cout << concorde;

    mercedes.refuel(mercedes.get_fuel_max()-mercedes.get_fuel());
    std::cout << mercedes;
    bmw.refuel(bmw.get_fuel_max()-bmw.get_fuel());
    std::cout << bmw;
    zodiac.refuel(zodiac.get_fuel_max()-zodiac.get_fuel());
    std::cout << zodiac;
    concorde.refuel(concorde.get_fuel_max()-concorde.get_fuel());
    std::cout << concorde;

    std::cout << "vehicule_t::get_nkm(): " << vehicules_t::get_nkm() << "\n";
    std::cout << "car_t::get_nkm(): " << car_t::get_nkm() << "\n";
    std::cout << "boat_t::get_nkm(): " << boat_t::get_nkm() << "\n";
    std::cout << "plane_t::get_nkm(): " << plane_t::get_nkm() << "\n";

    return 0;
}