import java.util.List;

public class SimSystem {
    private final int processCount;
    private final int resourceCount;
    private int[][] maxMatrix;
    private int[][] allocationMatrix;
    private int[][] needMatrix;
    private int[] resourceVector;

    public SimSystem(List<String> arr) {
        this.processCount = Integer.parseInt(arr.get(0));
        this.resourceCount = Integer.parseInt(arr.get(1));
        this.maxMatrix = new int[this.processCount][this.resourceCount];
        this.resourceVector = new int[this.resourceCount];
        this.allocationMatrix = new int[this.processCount][this.resourceCount];

        int pointer = 2;
        for (int i = 0; i < processCount; i++) {
            for (int j = 0; j < resourceCount; j++) {
                this.maxMatrix[i][j] = Integer.parseInt(arr.get(pointer));
                pointer++;
            }
        }
        this.needMatrix = this.maxMatrix;

        for (int i = 0; i < resourceCount; i++) {
            this.resourceVector[i] = Integer.parseInt(arr.get(pointer));
            pointer++;
        }
    }

    // TODO: make the printing account for offset of more then 1 digit values
    public void sysPrint() {
        System.out.println("Process    Allocation    Max    Resources    Need");
        System.out.println("             A B C      A B C    A B C      A B C");

        int n = processCount;
        int m = resourceCount;
        for (int i = 0; i < n; i++) {
            System.out.print("  P" + i + "         ");
            for (int j = 0; j < m; j++) {
                System.out.print(allocationMatrix[i][j] + " ");
            }
            System.out.print("     ");
            for (int j = 0; j < m; j++) {
                System.out.print(maxMatrix[i][j] + " ");
            }
            System.out.print("   ");
            if (i == 0) {
                for (int j = 0; j < m; j++) {
                    System.out.print(resourceVector[j] + " ");
                }
            } else {
                System.out.print("      ");
            }
            System.out.print("     ");
            for (int j = 0; j < m; j++) {
                System.out.print(needMatrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    public int getProcessCount() {
        return processCount;
    }

    public int getResourceCount() {
        return resourceCount;
    }

    public int[][] getMaxMatrix() {
        return maxMatrix;
    }

    public void setMaxMatrix(int[][] maxMatrix) {
        this.maxMatrix = maxMatrix;
    }

    public int[][] getAllocationMatrix() {
        return allocationMatrix;
    }

    public void setAllocationMatrix(int[][] allocationMatrix) {
        this.allocationMatrix = allocationMatrix;
    }

    public int[][] getNeedMatrix() {
        return needMatrix;
    }

    public void setNeedMatrix(int[][] needMatrix) {
        this.needMatrix = needMatrix;
    }

    public int[] getResourceVector() {
        return resourceVector;
    }

    public void setResourceVector(int[] resourceVector) {
        this.resourceVector = resourceVector;
    }
}
