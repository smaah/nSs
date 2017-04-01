#include <iostream>

#include "VTKFileWriter.hh"
#include "Debug.hh"


VTKFileWriter::VTKFileWriter(const std::vector< int >& dimension,
	const std::vector< double >& length, const std::string& problem )
    :mDim(dimension)
{
  cout<<"*****************************************************"<<endl;
  cout<<"               Setting output to file:"<<problem<<"  "<<endl;
  cout<<"*****************************************************"<<endl;

    std::string filename = "./results/" +problem;
    filename += ".vtk";
    mStream = fopen(filename.c_str(), "w");

    if ( mStream == NULL )
    {
      ERROR("Error opening outputfile");
    }

    fprintf( mStream, "# vtk DataFile Version 4.0\n");
    fprintf( mStream, "Nusif %s\n",problem.c_str());
    fprintf( mStream, "ASCII\n");
    fprintf( mStream, "DATASET STRUCTURED_POINTS\n");

    switch( mDim.size() )
    {
        case 1:
            mDataCount = mDim[0];
            fprintf( mStream, "DIMENSIONS %d 1 1\n",mDim[0]);
            fprintf( mStream, "ORIGIN 0 0 0 \n" );
            fprintf( mStream, "SPACING %f 1 1\n",length[0]);
            break;
        case 2:
            mDataCount = mDim[0]*mDim[1];
            fprintf( mStream, "DIMENSIONS %d %d 1\n",mDim[0],mDim[1]);
            fprintf( mStream, "ORIGIN 0 0 0 \n" );
            fprintf( mStream, "SPACING %f %f 1\n",length[0],length[1]);
            break;
        case 3:
            mDataCount = mDim[0]*mDim[1]*mDim[2];
            fprintf( mStream, "DIMENSIONS %d %d %d\n",mDim[0],mDim[1],mDim[2]);
            fprintf( mStream, "ORIGIN 0 0 0 \n" );
            fprintf( mStream, "SPACING %f %f %f\n",length[0],length[1],length[2]);
            break;
        default:
	  ERROR("Unsupported Dimension "<<mDim.size());
    }
    fprintf( mStream, "POINT_DATA %d\n\n", mDataCount);
}



VTKFileWriter::~VTKFileWriter( )
{
    fprintf( mStream, "\n" );
    fclose(mStream);
}


void VTKFileWriter::WriteVector(const std::vector<std::vector< double > >& vec,
        const  std::string& name)
{
  cout<<"*****************************************************"<<endl;
  cout<<"Register Vector: "<<name<<" with dimension "<<vec.size()<<endl;
  cout<<"*****************************************************"<<endl;

    fprintf( mStream, "VECTORS %s double\n", name.c_str());
    
    switch( vec.size() )
    {
        case 2:
            for(int i=0, end = vec[0].size(); i<end; i++)
            {
                for(int dim=0, iend=vec.size(); dim<iend; dim++)
                {
                    fprintf( mStream, "%0.13f ", vec[dim][i]);
                }
                fprintf( mStream, "0\n");
            }
            break;

        case 3:
            for(int i=0, end = vec[0].size(); i<end; i++)
            {
                for(int dim=0, iend=vec.size(); dim<iend; dim++)
                {
                    fprintf( mStream, "%f ", vec[dim][i]);
                }
                fprintf( mStream, "\n ");
            }
            break;
        default:
	  ERROR("Unsupported Dimension "<<vec.size());
	  ;    }

}


void VTKFileWriter::WriteScalar(const std::vector<double>& scalar,
        const  std::string& name)
{
  cout<<"*****************************************************"<<endl;
  cout<<"Register Scalar: "<<name<<endl;
  cout<<"*****************************************************"<<endl;

    fprintf( mStream, "SCALARS %s double 1\n",name.c_str() );
    fprintf( mStream, "LOOKUP_TABLE default\n");
    cout<<scalar.size()<<endl;
    for(int i=0, end=scalar.size(); i<end; i++)
    {
        fprintf( mStream, "%0.13f\n", scalar[i] );
    }
}


