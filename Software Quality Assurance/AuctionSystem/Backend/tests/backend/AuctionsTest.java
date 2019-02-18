package tests.backend;

import backend.Auctions;
import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

import backend.Users;

public class AuctionsTest {
    /**
     * Test of load method, of class Auctions.
     */
    @Test
    public void testLoad() throws Exception {
        System.out.println("Testing load()...");
        String filename = "auctions.txt";
        Auctions instance = new Auctions();
        instance.load(filename);
    }

    /**
     * Test of advertise method, of class Auctions.
     */
    @Test
    public void testAdvertise() {
        System.out.println("Testing advertise()...");
        String transaction = "03 computer             ss01           admin01         010 100.00";
        Auctions instance = new Auctions();
        instance.advertise(transaction);
    }

    /**
     * Test of bid method, of class Auctions.
     */
    @Test
    public void testBid() throws Exception{
        System.out.println("Testing bid()...");
        String transaction = "05 Toaster                   SS TestUser      FS TestUser      015.00";
        Auctions instance = new Auctions();
        instance.load("auction.txt");
        instance.bid(transaction);
    }

    /**
     * Test of delete method, of class Auctions.
     */
    @Test
    public void testDelete() throws Exception{
        System.out.println("Testing delete()...");
        String item = "computer";
        String seller = "s01";
        Auctions instance = new Auctions();
        instance.load("auction.txt");
        instance.delete(item, seller);
    }

    /**
     * Test of endDday method, of class Auctions.
     */
    @Test
    public void testEndDay() throws Exception{
        System.out.println("Testing endDday()...");
        Auctions instance = new Auctions();
        instance.load("auction.txt");
        Users users = new Users();
        instance.endDay(users);
    }

    /**
     * Test of write method, of class Auctions.
     */
    @Test
    public void testWrite() throws Exception {
        System.out.println("testing write()...");
        String filename = "output.txt";
        Auctions instance = new Auctions();
        instance.load("auction.txt");
        instance.write(filename);
    }
    
}
