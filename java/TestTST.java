public class TestTST {
	static class PrintAction extends Action {
		public void perform(String key, int remaining_distance, Object data) {
			System.out.println(key);
		}
	}

    public static void main(String[] args) throws Exception {
        System.loadLibrary("jtst");
        
        Action aP=new Action("toto");
        aP.perform("Coucou",0,"Coucou");

        JavaTST tP=new JavaTST();
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
            tP.put(keyP,keyP);
        }
        endP=System.currentTimeMillis();
        System.out.println("Write : "+(1.0*(endP-startP)/1000));
        
        tP.pack();
        
        startP=System.currentTimeMillis();
        for(int iP=0;iP<4000000;iP++) {
            String keyP=Integer.toString(iP);
            tP.get(keyP);
        }
        endP=System.currentTimeMillis();
        System.out.println("Read : "+(1.0*(endP-startP)/1000));
                
        tP.scan("35465432132123431.2131324135431321",new Action("toto"));
        
        System.gc();
        System.gc();
        System.gc();
        
        System.out.println("OK");
        System.in.read();
    }
}
