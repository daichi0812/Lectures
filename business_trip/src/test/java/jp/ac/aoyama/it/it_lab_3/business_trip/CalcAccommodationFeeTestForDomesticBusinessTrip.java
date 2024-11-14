package jp.ac.aoyama.it.it_lab_3.business_trip;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.kie.api.KieServices;
import org.kie.api.runtime.KieContainer;
import org.kie.api.runtime.KieSession;

public class CalcAccommodationFeeTestForDomesticBusinessTrip {

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
    public void domesticBusinessTripCalcAccommodationFeeTest1() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", 2);
        btm.setNumberOfNights(1);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getAccommodationFee();
        int expected = 12000;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void domesticBusinessTripCalcAccommodationFeeTest2() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", 3);
        btm.setNumberOfNights(2);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getAccommodationFee();
        int expected = btm.getNumberOfNights() * 12000;
        Assertions.assertEquals(expected, actual);
    }

}
