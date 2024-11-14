package jp.ac.aoyama.it.it_lab_3.business_trip;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.kie.api.KieServices;
import org.kie.api.runtime.KieContainer;
import org.kie.api.runtime.KieSession;

public class CalcAccommodationFeeTestForOverseasBusinessTrip {

    private KieSession ksession;

    @BeforeEach
    public void initialize() {
        KieContainer kc = KieServices.get().getKieClasspathContainer();
        ksession = kc.newKieSession("BusinessTripKS");
    }

    @AfterEach
    public void dispose() {
        ksession.dispose();
    }

    @Test
    public void overseasBusinessTripCalcDailyAllowanceTest1() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国外", 5);
        btm.setJobTitle("教授");
        btm.setLocation("シンガポール");
        btm.setNumberOfNights(4);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getAccommodationFee();
        int expected = btm.getNumberOfNights() * 21000;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void overseasBusinessTripCalcDailyAllowanceTest2() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国外", 5);
        btm.setJobTitle("教授");
        btm.setLocation("ローマ");
        btm.setNumberOfNights(4);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getAccommodationFee();
        int expected = btm.getNumberOfNights() * 19000;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void overseasBusinessTripCalcDailyAllowanceTest3() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国外", 5);
        btm.setJobTitle("准教授");
        btm.setLocation("シンガポール");
        btm.setNumberOfNights(4);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getAccommodationFee();
        int expected = btm.getNumberOfNights() * 19000;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void overseasBusinessTripCalcDailyAllowanceTest4() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国外", 5);
        btm.setJobTitle("准教授");
        btm.setLocation("ローマ");
        btm.setNumberOfNights(4);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getAccommodationFee();
        int expected = btm.getNumberOfNights() * 17000;
        Assertions.assertEquals(expected, actual);
    }
}
