#include "phone_number.h"
#include <sstream>


PhoneNumber::PhoneNumber(const string &international_number){
    if(international_number[0]!='+'){
        throw invalid_argument("the first sign must be a plus");
    }
    else{
        istringstream is(international_number);
        is.get();
        getline(is, country_code_, '-');
        getline(is, city_code_, '-');
        getline(is, local_number_);
        if(country_code_.empty()||city_code_.empty()||local_number_.empty()){
            throw invalid_argument("invalid number");
        }
    }
}
string PhoneNumber::GetCountryCode() const{
    return country_code_;
}
string PhoneNumber::GetCityCode() const{
    return city_code_;
}
string PhoneNumber::GetLocalNumber() const{
    return local_number_;
}
string PhoneNumber::GetInternationalNumber() const{
    return "+"+country_code_+"-"+city_code_+"-"+local_number_;
}
