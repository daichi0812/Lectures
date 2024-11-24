/*
* 15822108 情報テクノロジー学科 堀田大智
* */
package org.drools.examples.helloworld;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.kie.api.KieServices;
import org.kie.api.runtime.KieContainer;
import org.kie.api.runtime.KieSession;

public class HelloWorldExampleTest {

    private KieSession ksession;

    @BeforeEach
    public void initialize() {
        KieContainer kc = KieServices.get().getKieClasspathContainer();
        ksession = kc.newKieSession("HelloWorldKS");
    }

    @AfterEach
    public void dispose() {
        ksession.dispose();
    }

    @Test
    public void helloTest() {
        Message message = new Message();
        message.setStatus(Message.HELLO);
        ksession.insert(message);
        ksession.fireAllRules();
        String actual = message.getMessage();
        String expected = "Hello!";
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void goodMorningTest() {
        Message message = new Message();
        message.setStatus(Message.GOOD_MORNING);
        ksession.insert(message);
        ksession.fireAllRules();
        String actual = message.getMessage();
        String expected = "Good Morning!";
        Assertions.assertEquals(expected, actual);
    }

    @Test
    public void goodbyeTest() {
        Message message = new Message();
        message.setStatus(Message.GOODBYE);
        ksession.insert(message);
        ksession.fireAllRules();
        String actual = message.getMessage();
        String expected = "Goodbye!";
        Assertions.assertEquals(expected, actual);
    }
}
