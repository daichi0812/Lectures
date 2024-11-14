/* 15822108 情報テクノロジー学科 堀田大智*/
package jp.ac.aoyama.it.it_lab_3.business_trip;

public class BusinessTripModel {
    private String name;
    private String jobTitle;
    private String travelCategory;
    private int dailyAllowance;
    private int accommodationFee;
    private int numberOfNights;
    private int travelDays;
    private int travelHours;
    private String location;
    private String cityType;

    BusinessTripModel(String name, String travelCategory, int travelDays){
        this.name = name;
        this.travelCategory = travelCategory;
        this.travelDays = travelDays;
        this.dailyAllowance = -1;
        this.travelHours = -1;
    }

    public String getName(){
        return name;
    }

    public void setName(String name){
        this.name = name;
    }

    public String getJobTitle(){
        return jobTitle;
    }

    public void setJobTitle(String jobTitle){
        this.jobTitle = jobTitle;
    }

    public int getDailyAllowance(){
        return dailyAllowance;
    }

    public void setDailyAllowance(int dailyAllowance){
        this.dailyAllowance = dailyAllowance;
    }

    public int getAccommodationFee(){
        return accommodationFee;
    }

    public void setAccommodationFee(int accommodationFee){
        this.accommodationFee = accommodationFee;
    }

    public int getNumberOfNights(){
        return numberOfNights;
    }

    public void setNumberOfNights(int numberOfNights){
        this.numberOfNights = numberOfNights;
    }

    public int getTravelHours(){
        return travelHours;
    }

    public void setTravelHours(int travelHours){
        this.travelHours = travelHours;
    }

    public String getTravelCategory(){
        return travelCategory;
    }

    public void setTravelCategory(String travelCategory){
        this.travelCategory = travelCategory;
    }

    public int getTravelDays(){
        return travelDays;
    }

    public void setTravelDays(int travelDays){
        this.travelDays = travelDays;
    }

    public String getLocation(){
        return location;
    }

    public void setLocation(String location){
        this.location = location;
    }

    public String getCityType(){
        return cityType;
    }

    public void setCityType(String cityType){
        this.cityType = cityType;
    }
}
