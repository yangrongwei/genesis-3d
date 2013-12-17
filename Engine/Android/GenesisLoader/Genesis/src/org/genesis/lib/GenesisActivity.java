/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
Copyright (c) 2011-2013,WebJet Business Division,CYOU

http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.genesis.lib;

import org.genesis.lib.GenesisGLSurfaceView;
import org.genesis.lib.GenesisHelperListener;

import com.genesis.R;

import android.app.Activity;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.PaintDrawable;
import android.os.Bundle;
import android.os.Message;
import android.view.ViewGroup;
import android.widget.FrameLayout;

public abstract class GenesisActivity extends Activity implements GenesisHelperListener {
	// ===========================================================
	// Constants
	// ===========================================================
	private static final String TAG = GenesisActivity.class.getSimpleName();
	// ===========================================================
	private GenesisGLSurfaceView mGLSurefaceView;
	
	public GenesisGLSurfaceView GetSurfaceView()
	{
		return mGLSurefaceView;
	}
	
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.init();
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	@Override
	protected void onResume() {
		super.onResume();
		
		
		this.mGLSurefaceView.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();

		
		this.mGLSurefaceView.onPause();
	}
	
	@Override
	protected void onStop()
	{
		super.onStop();
		
		this.mGLSurefaceView.onStop();
	}
	
	
	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		this.mGLSurefaceView.onDestroy();
	}
	

	@Override
	public void showDialog(final String pTitle, final String pMessage) {
		Message msg = new Message();
	}

	@Override
	public void showEditTextDialog(final String pTitle, final String pContent, final int pInputMode, final int pInputFlag, final int pReturnType, final int pMaxLength) { 
	
	}
	
	@Override
	public void runOnGLThread(final Runnable pRunnable) {
		this.mGLSurefaceView.queueEvent(pRunnable);
	}
	  public void init() {
	    			
	    	// FrameLayout
	        ViewGroup.LayoutParams framelayout_params =
	            new ViewGroup.LayoutParams(ViewGroup.LayoutParams.FILL_PARENT,
	                                       ViewGroup.LayoutParams.FILL_PARENT);
	        FrameLayout framelayout = new FrameLayout(this);
	        framelayout.setLayoutParams(framelayout_params);

	   	        // Cocos2dxGLSurfaceView
	        this.mGLSurefaceView = new GenesisGLSurfaceView(this);

	        // ...add to FrameLayout
	        framelayout.addView(mGLSurefaceView);
	        mGLSurefaceView.setBackgroundResource(R.drawable.load);
		
	        mGLSurefaceView.setGenesisRenderer(new GenesisRenderer(this));
	        
	        // Set framelayout as the content view
			setContentView(framelayout);
	    }
	    
}