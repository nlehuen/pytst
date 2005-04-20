public class TestTST {
    public static void main(String[] args) throws Exception {
        System.loadLibrary("jtst");
        
        JavaTST tP=new JavaTST(256,null);
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
        
        System.gc();
        System.gc();
        System.gc();
        
        System.in.read();
    }
}
