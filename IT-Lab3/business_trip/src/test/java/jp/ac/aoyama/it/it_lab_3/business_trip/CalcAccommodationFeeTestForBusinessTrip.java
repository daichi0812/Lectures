package jp.ac.aoyama.it.it_lab_3.business_trip;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.kie.api.KieServices;
import org.kie.api.runtime.KieContainer;
import org.kie.api.runtime.KieSession;

public class CalcAccommodationFeeTestForBusinessTrip {
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
    public void businessTripCalcAccommodationFeeTest1() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", 0);
        btm.setNumberOfNights(0);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getAccommodationFee();
        int expected = 0;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void businessTripCalcAccommodationFeeTest2() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国外", 0);
        btm.setNumberOfNights(0);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getAccommodationFee();
        int expected = 0;
        Assertions.assertEquals(expected, actual);
    }
}
