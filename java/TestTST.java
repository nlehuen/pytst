import java.util.*;

public class TestTST {
	public native Object test(String key, int oto,Object data);

    public static void main(String[] args) throws Exception {
        System.loadLibrary("jtst");
        
        ObjectAction aP=new ObjectAction(new TestTST(),"perform","result");
		aP.perform("Coucou",0,"Coucou");
		System.out.println(aP.result());

        ObjectTST tP=new ObjectTST("DEFAUT");
        long startP,endP;
        

        startP=System.currentTimeMillis();
        for(int iP=0;iP<4000000;iP++) {
            String keyP=Integer.toString(iP);
        }
        endP=System.currentTimeMillis();
        System.out.println("Build : "+(1.0*(endP-startP)/1000));

		startP=System.currentTimeMillis();
        for(int iP=0;iP<4000000;iP++) {
            String keyP=Integer.toString(iP);
			Object oP="coucou "+keyP;
            tP.put(keyP,oP);
        }
        endP=System.currentTimeMillis();
        System.out.println("Write : "+(1.0*(endP-startP)/1000));
        
        tP.pack();
        
        startP=System.currentTimeMillis();
        for(int iP=0;iP<4000000;iP++) {
            String keyP=Integer.toString(iP);
            System.out.println(tP.get(keyP));
        }
        endP=System.currentTimeMillis();
        System.out.println("Read : "+(1.0*(endP-startP)/1000));
                
        tP.scan("35465432132123431.2131324135431321",new ObjectAction(new TestTST(),"toto",null));
        
        System.gc();
        System.gc();
        System.gc();
        
        System.out.println("OK");
        System.in.read();
    }

	public void perform(String key,int remaining_distance,Object data) {
		System.out.println("From java : "+key+" "+remaining_distance+" "+data);
	}

	public Object result() {
		return "Bonjour";
	}
}
