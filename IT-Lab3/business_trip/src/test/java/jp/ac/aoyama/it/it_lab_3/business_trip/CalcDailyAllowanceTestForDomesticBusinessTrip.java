package jp.ac.aoyama.it.it_lab_3.business_trip;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.kie.api.KieServices;
import org.kie.api.runtime.KieContainer;
import org.kie.api.runtime.KieSession;

public class CalcDailyAllowanceTestForDomesticBusinessTrip {

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
    public void domesticBusinessTripCalcDailyAllowanceTest1() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", 0);
        btm.setTravelHours(3);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getDailyAllowance();
        int expected = 0;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void domesticBusinessTripCalcDailyAllowanceTest2() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", 0);
        btm.setTravelHours(5);
        btm.setLocation("東京都");
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getDailyAllowance();
        int expected = 1500;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void domesticBusinessTripCalcDailyAllowanceTest3() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", 0);
        btm.setTravelHours(5);
        btm.setLocation("神奈川県");
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getDailyAllowance();
        int expected = 1500;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void domesticBusinessTripCalcDailyAllowanceTest4() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", 0);
        btm.setTravelHours(5);
        btm.setLocation("千葉県");
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getDailyAllowance();
        int expected = 1500;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void domesticBusinessTripCalcDailyAllowanceTest5() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", 0);
        btm.setTravelHours(5);
        btm.setLocation("埼玉県");
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getDailyAllowance();
        int expected = 1500;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void domesticBusinessTripCalcDailyAllowanceTest6() {
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", 0);
        btm.setTravelHours(5);
        btm.setLocation("静岡県");
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getDailyAllowance();
        int expected = 3000;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void domesticBusinessTripCalcDailyAllowanceTest7() {
        int travelDays = 1;
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", travelDays);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getDailyAllowance();
        int expected = travelDays * 3000;
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void domesticBusinessTripCalcDailyAllowanceTest8() {
        int travelDays = 2;
        BusinessTripModel btm = new BusinessTripModel("山田太郎", "国内", travelDays);
        ksession.insert(btm);
        ksession.fireAllRules();
        int actual = btm.getDailyAllowance();
        int expected = travelDays * 3000;
        Assertions.assertEquals(expected, actual);
    }

}
