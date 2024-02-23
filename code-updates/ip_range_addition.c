/* IP RANGE Upgrade */
/* Author Nasantogtokh Amarsaikhan */
/* MUST - CSMS */
/* Student ID: D.HW09D402 */
/* Date: 2012-12-26 */


/**** BEGIN ****/


for ( i = 0; i < 20 ; i++ )
{
a[i]=RANGE[i];	//"range"-n buh utgiig too helbereer "a"-ruu huulj avah;
}
for(i = 0; i < 20; i++)
{
if (a[i]==46) //hamgiin suuliin "."-temdegtiin index-g ni "coma"-ruu hadgalah; 
{	
					++coma;
						if(coma==3)
						coma=i;
					}
if (a[i]==45) 	//"-" temdegtees hoish 3 uragsh 3 temdegtiing "low" bolon "high" ruu huulj avah
						{
						low[0]=a[i-3];
						low[1]=a[i-2];
						low[2]=a[i-1];
						high[0]=a[i+1];
						high[1]=a[i+2];
						high[2]=a[i+3];						
						}
				}
if ( low [0] != 46 && low [1] !=46 && low [2] !=46 ) /* "low" bolon "high"-g zadalj "l" bolon "h" int helbereer oruulah  */
			{
			l=(low[2]-48)+(low[1]-48)*10+(low[0]-48)*100;
			}
		else if (low[0]==46 && low[1]!=46 && low[2]!=46 )
			{
			l=(low[1]-48)*10+(low[2]-48);
			}
		else if (low[0]!=46 && low[1]==46 && low[2]!=46 )
			{
			l=low[2]-48;
			}
		if ( high [1] !=0 && high[2]!=0 )
			{
			h=(high[0]-48)*100+(high[1]-48)*10+high[2]-48;
			}
		else if ( high [1] !=0 && high[2]==0 )
			{
			h=(high[0]-48)*10+high[1]-48;
			}
		else if ( high [1] == 0 && high[2]==0 )
			{
			h=high[0]-48;
			}
if(l<0 || h<0 || l>255 || h>255){ //hervee ip hayagiin range buruu bval aldaa shideed gargana;
fprintf(stderr, "THIS IS NOT IP ADDRESS !!! \n");
quit(0);
}
RANGE[coma+4]=RANGE[coma+5]=RANGE[coma+6]=0;
for(l; l<=h; l++){    /* RANGE-g "l"-ees "h" hurtel davtaj tuunii utgiig ni RANGE-d olgoh */
				if (l>=100)
				{
				RANGE[coma+1]=l/100+48;
				RANGE[coma+2]=(l-l/100*100)/10+48;
				RANGE[coma+3]=(l-l/100*100-(l-l/100*100)/10*10)+48;
				}
				else if (l>=10 && l<100){
				RANGE[coma+3]=0;
				RANGE[coma+1]=l/10+48;
				RANGE[coma+2]=l-(l/10)*10+48;
				}
				else if(l>=1 && l<10){
				RANGE[coma+3]=RANGE[coma+2]=0;
				RANGE[coma+1]=l+48;
				}
				fprintf(stdout, "RANGE OF IP : %s   \n",RANGE);

/**** END ****/