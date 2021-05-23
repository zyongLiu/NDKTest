package com.liu.opencvdemo;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() {
        assertEquals(4, 2 + 2);
    }

    /**
     *       L     M     R
     *   |-------|---|-------|
     *   | 0 1 2 | 4 | 5 6 7 |
     *   | 7 0 1 | 2 | 4 5 6 |
     * T | 6 7 0 | 1 | 2 4 5 |
     *   | 5 6 7 | 0 | 1 2 4 |
     *   |-------|---|-------|
     *   | 4 5 6 | 7 | 0 1 2 |
     * B | 2 4 5 | 6 | 7 0 1 |
     *   | 1 2 4 | 5 | 6 7 0 |
     *   |-------|---|-------|
     */
    /**
     *
     * @param A int整型一维数组
     * @param target int整型
     * @return int整型
     */
    public int search (int[] A, int target) {

    }

    /**
     * 二分查找针对有序数组
     * @param A
     * @param target
     * @return
     */
    public int binarySearch(int[] A,int target){
        int lo=0,he=A.length-1,mid=A.length/2;
        if (A[lo]>target||A[he]<target){
            return -1;
        }
        while (lo<he){
            //在左边
            if (A[lo]<=target&&A[mid]>target){
                he=mid-1;
            }else if (A[he]>=mid&&A[mid]<target){
                lo=mid+1;
            }else {
                return mid;
            }
            mid=(lo+he)/2;
        }
        return -1;

    }
}