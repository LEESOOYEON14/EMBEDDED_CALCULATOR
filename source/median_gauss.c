#include<stdio.h>
#include<stdlib.h>

void comment(FILE *fp)
{
    int ch;
    char line[100];

    while ((ch = fgetc(fp)) != EOF && isspace(ch));
    if (ch == '#') {
        fgets(line, sizeof(line), fp);
        printf("%s",line);
        comment(fp);
    } else
        fseek(fp, -1, SEEK_CUR);
}


int main()
{
    char ver[2],c;
    int row,col,x;
    int max,i,j;


    //read the pgm file
    FILE *f;
    printf("\nEnter the file name with extension:");
    char name[20];
    scanf("%s",name);
    f=fopen(name,"rb");
    fscanf(f,"%s",ver);
    ver[2]='\0';
    printf("%s",ver);
    comment(f);
    fscanf(f,"%d",&col);
    comment(f);
    fscanf(f,"%d",&row);
    comment(f);
    fscanf(f,"%d",&max);
    comment(f);
  printf("%c%d %d %d",c,row, col, max);
    int **a=(int **)malloc(sizeof(int*)*row);
    for(i=0;i<row;i++)
        a[i]=(int *)malloc(sizeof(int)*col);
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
        {
            fscanf(f,"%c",&a[i][j]);
        }
 /*  printf("\nThe elements of the image are:\n)");
        for(i=0;i<row;i++)
           {

            for(j=0;j<col;j++)
            {
                printf("%d ",a[i][j]);
            }
           printf("\n");
           }*/
fclose(f);


int r;
printf("\nChoose one..\n1.Median Filter\n2.Gaussian Filter");
scanf("%d",&r);
//median filter
int k,l,m,n,*window,ctr=0,swap,e,d;
switch(r)
{
case 1:
printf("\nFor Median Filter, specify the size of the window (nxn), enter n(odd):");
int wins;
scanf("%d",&wins);



 window=(int*)malloc(sizeof(int)*wins*wins);

 for(i=0;i<row;i++)
{
    for(j=0;j<col;j++)
   {
     if(a[i][j]<20||a[i][j]>220)
     {ctr=0;
     if((i-(wins/2))<0)  /*check if window lies outside the array or not*/
        k=0;
     else
       k=i-(wins/2);

     if((j-(wins/2))<0)
        l=0;
     else
        l=j-(wins/2);

     for(m=k;(m<=i+(wins/2))&&(m<row);m++)

        for(n=l;(n<=j+(wins/2))&&(n<col);n++)
          window[ctr++]=a[m][n];

}

 for (e=0;e<(ctr-1);e++)      /*sorting the window array*/
  {
    for (d=0;d<ctr-e-1;d++)
    {
      if (window[d]>window[d+1])
      {
        swap       = window[d];
        window[d]   = window[d+1];
        window[d+1] = swap;
      }
    }
  }
  if(ctr%2==0)
  a[i][j]=(window[(ctr-1)/2]+window[((ctr-1)/2)+1])*0.5;  /*if there are two medians*/
  else
  a[i][j]=window[(ctr-1)/2];

   }

   }

   break;


case 2: ctr=0; wins=3;int sumg=0;
float g[3][3]={{0.01,0.08,0.01},{0.08,0.64,0.08},{0.01,0.08,0.01}};int o,p;


int z;
 float wind[9];
//for(z=0;z<;z++)
 for(i=0;i<row;i++)
    for(j=0;j<col;j++)
   {

     ctr=0;
     if((i-(wins/2))<0)  /*check if window lies outside the array or not*/
        k=0;
     else
       k=i-(wins/2);

     if((j-(wins/2))<0)
        l=0;
     else
        l=j-(wins/2);

     for(m=k,o=0;(m<=i+1)&&(m<row)&&o<3;m++,o++)

        for(n=l,p=0;(n<=j+1)&&(n<col)&&p<3;n++,p++)
          wind[ctr++]=(a[m][n]*1.0)*g[o][p];
for(e=0;e<ctr;e++)
    sumg+=wind[e];
   a[i][j]=sumg;



   }
}








//writing the data to a new file

f=fopen("test.pgm","wb");
fprintf(f,"%c%c %d %d %d\n",ver[0],ver[1],col,row,max);

 for(i=0;i<row;i++)
           {

            for(j=0;j<col;j++)
            {
                fprintf(f,"%c",a[i][j]);
            }
           }
printf("\nCopied");
fclose(f);
return 1;
}
