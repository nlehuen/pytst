import java.util.*;

public class TestTST2 {
	public native Object test(String key, int oto,Object data);

    public static void main(String[] args) throws Exception {
        System.loadLibrary("jtst");
        
        LongAction aP=new LongAction(new TestTST2(),"perform","result");
		aP.perform("Coucou",0,23041976L);
		System.out.println(aP.result());

        LongFilter fP=new LongFilter(new TestTST2(),"filter");
		System.out.println(fP.perform("Coucou",0,23041976L));

        LongTST tP=new LongTST(256,-987987L);
        long startP,endP;
        
        startP=System.currentTimeMillis();
        for(int iP=0;iP<4000000;iP++) {
            String keyP=Integer.toString(iP);
        }
        endP=System.currentTimeMillis();
        System.out.println("Build : "+(1.0*(endP-startP)/1000));

        System.gc();
        System.gc();
        System.gc();

		HashMap mP=new HashMap();
        startP=System.currentTimeMillis();
        for(int iP=0;iP<4000000;iP++) {
            String keyP=Integer.toString(iP);
            mP.put(keyP,new Long(iP));
        }
        endP=System.currentTimeMillis();
        System.out.println("HashMap Write : "+(1.0*(endP-startP)/1000));

        startP=System.currentTimeMillis();
        for(int iP=0;iP<4000000;iP++) {
            String keyP=Integer.toString(iP);
            mP.get(keyP);
        }
        endP=System.currentTimeMillis();
        System.out.println("HashMap Read : "+(1.0*(endP-startP)/1000));

        System.out.println("OK 1");
        System.in.read();

		mP = null;
        System.gc();
        System.gc();
        System.gc();

        System.out.println("OK 2");
        System.in.read();

		startP=System.currentTimeMillis();
        for(int iP=0;iP<4000000;iP++) {
            String keyP=Integer.toString(iP);
            tP.put(keyP,iP);
        }
        endP=System.currentTimeMillis();
        System.out.println("Write : "+(1.0*(endP-startP)/1000));
        
        tP.pack();

        System.gc();
        System.gc();
        System.gc();
        
        startP=System.currentTimeMillis();
        for(int iP=0;iP<4000000;iP++) {
            String keyP=Integer.toString(iP);
            tP.get(keyP);
        }
        endP=System.currentTimeMillis();
        System.out.println("Read : "+(1.0*(endP-startP)/1000));
                
        // tP.scan("35465432132123431.2131324135431321",new ObjectAction(new TestTST2(),"perform",null));
        
        System.gc();
        System.gc();
        System.gc();
        
        System.out.println("OK 3");
        System.in.read();
    }

	public void perform(String key,int remaining_distance,long data) {
		System.out.println("Action from java : "+key+" "+remaining_distance+" "+data);
	}

	public long result() {
		System.out.println("Result from java");
		return 19530406L;
	}
	
	public long filter(String key,int remaining_distance,long data) {
		System.out.println("Filter from java : "+key+" "+remaining_distance+" "+data);
		return data+1L;
	}	
}
