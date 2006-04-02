import java.util.*;
import com.lehuen.tst.*;

public class TestTST {
	public static final int ITERATIONS=100000;

    public static void main(String[] args) throws Exception {
        System.loadLibrary("jtst");

        ObjectAction aP=new ObjectAction(new TestTST(),"perform","result");
		aP.perform("Perform test",0,"is it working ?");
		System.out.println(aP.result());

		ObjectFilter fP=new ObjectFilter(new TestTST(),"filter");
		System.out.println(fP.perform("Filter test",0,"it works !"));

        ObjectTST tP=new ObjectTST(256,"DEFAUT");
        long startP,endP;
        

        startP=System.currentTimeMillis();
        for(int iP=0;iP<ITERATIONS;iP++) {
            String keyP=Integer.toString(iP);
        }
        endP=System.currentTimeMillis();
        System.out.println("Build : "+(1.0*(endP-startP)/1000));

        System.gc();
        System.gc();
        System.gc();

		HashMap mP=new HashMap();
        startP=System.currentTimeMillis();
        for(int iP=0;iP<ITERATIONS;iP++) {
            String keyP=Integer.toString(iP);
            mP.put(keyP,keyP);
        }
        endP=System.currentTimeMillis();
        System.out.println("HashMap Write : "+(1.0*(endP-startP)/1000));

        startP=System.currentTimeMillis();
        for(int iP=0;iP<ITERATIONS;iP++) {
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
        for(int iP=0;iP<ITERATIONS;iP++) {
            String keyP=Integer.toString(iP);
            tP.put(keyP,keyP);
        }
        endP=System.currentTimeMillis();
        System.out.println("Write : "+(1.0*(endP-startP)/1000));
        
        tP.pack();

        System.gc();
        System.gc();
        System.gc();
        
        startP=System.currentTimeMillis();
        for(int iP=ITERATIONS-1;iP>=0;iP--) {
            String keyP=Integer.toString(iP);
            if(!keyP.equals(tP.get(keyP))) {
				throw new RuntimeException("Probleme : "+keyP+" ==> "+tP.get(keyP));
            }
        }
        endP=System.currentTimeMillis();
        System.out.println("Read : "+(1.0*(endP-startP)/1000));
                
        System.gc();
        System.gc();
        System.gc();
        
        System.out.println("OK 3");
        System.in.read();

		System.out.println("Walk !");
		tP.walk(fP,aP);
	}

	public void perform(String key,int remaining_distance,Object data) {
		System.out.println("Perform java : \""+key+"\" "+remaining_distance+" "+data);
	}

	public Object result() {
		return "Yes it works !";
	}

	public Object filter(String key,int remaining_distance,Object data) {
		System.out.println("Filter java : \""+key+"\" "+remaining_distance+" "+data);
		return data;
	}
}
