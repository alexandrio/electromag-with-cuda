#include "CL Manager.h"
#include <iostream>

using namespace OpenCL;

ClManager GlobalClManager;
unsigned int ClManager::nrPlatforms;
ClManager::clPlatformProp *ClManager::platforms;

bool deviceMan::ComputeDeviceManager::deviceScanComplete = false;

deviceMan::ComputeDeviceManager::ComputeDeviceManager()
{
}

ClManager::ClManager()
{
    // Do a one-time scan for compatible GPUs
	if(!deviceScanComplete) ScanDevices();
    deviceScanComplete = true;
}

ClManager::~ClManager()
{
}

void ClManager::ScanDevices()
{
    nrPlatforms = 0;
    cl_int errCode = CL_SUCCESS;
    // Load the driver
    errCode = clLibLoad();
    if(errCode != CL_SUCCESS)
    {
        std::cerr<<" Failed to load OpenCL Library"<<std::endl;
        return;
    }

    // Query the number of platforms
    errCode = clGetPlatformIDs(0, 0, &nrPlatforms);
    if(errCode != CL_SUCCESS)
        std::cerr<<" Failed to get number of CL platforms with code "<<errCode<<std::endl;
    if(!nrPlatforms) return;

    // Temporary storage for the platform IDs
    cl_platform_id *platformIDs = new cl_platform_id[nrPlatforms];
    // Allocate resources for each platform
    platforms = new clPlatformProp[nrPlatforms];
    // Get the IDs of each platform
    errCode = clGetPlatformIDs(nrPlatforms, platformIDs, 0);
    if(errCode != CL_SUCCESS)
        std::cerr<<" Failed to get platform IDs with code "<<errCode<<std::endl;

    // Now fill the properties of each platform
    for(size_t i = 0; i< nrPlatforms; i++)
    {
        platforms[i].SetPlatformID(platformIDs[i]);
    }

    // Now that the PlatformIDs are recorded in the clPlatformProp structures
    // they are no longer needed separately
    delete[] platformIDs;
        
    
}



ClManager::clDeviceProp::clDeviceProp()
{

}

ClManager::clDeviceProp::~clDeviceProp()
{

}

void ClManager::clPlatformProp::SetPlatformID(cl_platform_id platID)
{
	this->platformID = platID;

    clGetPlatformInfo(this->platformID,
            CL_PLATFORM_NAME,
            sizeof(this->name),
            (void*)this->name,
            0);
   
    clGetPlatformInfo(this->platformID,
            CL_PLATFORM_VENDOR,
            sizeof(this->vendor),
            (void*)this->vendor,
            0);
   

    clGetPlatformInfo(this->platformID,
            CL_PLATFORM_PROFILE,
            sizeof(this->profile),
            (void*)this->profile,
            0);
  

    clGetPlatformInfo(this->platformID,
            CL_PLATFORM_VERSION,
            sizeof(this->version),
            (void*)this->version,
            0);
    
    clGetPlatformInfo(this->platformID,
            CL_PLATFORM_EXTENSIONS,
            sizeof(this->extensions),
            (void*)this->extensions,
            0);

    // Now get device details for this platform
    // Query the number of devices
    clGetDeviceIDs(this->platformID,
            CL_DEVICE_TYPE_ALL,
            0,
            0,
            &nrDevices);

    //Temporary storage for device IDs
    cl_device_id *deviceIDs = new cl_device_id[nrDevices];
    clGetDeviceIDs(this->platformID,
            CL_DEVICE_TYPE_ALL,
            nrDevices,
            deviceIDs,
            0);

    devices = new clDeviceProp[nrDevices];

    for(size_t i = 0; i < nrDevices; i++)
    {
        devices[i].SetDeviceID(deviceIDs[i]);
    }

    delete[] deviceIDs;

}


void ClManager::clDeviceProp::SetDeviceID(cl_device_id devID)
{
	this->deviceID = devID;
	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_ADDRESS_BITS,
			sizeof(this->addressBits),
            (void*)&this->addressBits,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_AVAILABLE,
			sizeof(this->available),
            (void*)&this->available,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_COMPILER_AVAILABLE,
			sizeof(this->compilerAvailable),
            (void*)&this->compilerAvailable,
            0);

	/*clGetDeviceInfo(this->deviceID,
            CL_DEVICE_DOUBLE_FP_CONFIG,
			sizeof(this->doubleFpConfig),
            (void*)&this->doubleFpConfig,
            0);
	*/
	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_ENDIAN_LITTLE,
			sizeof(this->littleEndian),
            (void*)&this->littleEndian,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_ERROR_CORRECTION_SUPPORT,
			sizeof(this->EccSupport),
            (void*)&this->EccSupport,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_EXECUTION_CAPABILITIES,
			sizeof(this->execCapabilities),
            (void*)&this->execCapabilities,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_EXTENSIONS,
			sizeof(this->extensions),
            (void*)this->extensions,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
			sizeof(this->globalMemCacheSize),
            (void*)&this->globalMemCacheSize,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
			sizeof(this->memCacheType),
            (void*)&this->memCacheType,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,
			sizeof(this->globalMemCachelineSize),
            (void*)&this->globalMemCachelineSize,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_GLOBAL_MEM_SIZE,
			sizeof(this->globalMemSize),
            (void*)&this->globalMemSize,
            0);

	/*clGetDeviceInfo(this->deviceID,
            CL_DEVICE_HALF_FP_CONFIG,
			sizeof(this->halfFpConfig),
            (void*)&this->halfFpConfig,
            0);
	*/
	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_IMAGE_SUPPORT,
			sizeof(this->imageSupport),
            (void*)&this->imageSupport,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_IMAGE2D_MAX_HEIGHT,
			sizeof(this->image2DMaxHeight),
            (void*)&this->image2DMaxHeight,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_IMAGE2D_MAX_WIDTH,
			sizeof(this->image2DMaxWidth),
            (void*)&this->image2DMaxWidth,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_IMAGE3D_MAX_DEPTH,
			sizeof(this->image3DMaxDepth),
            (void*)&this->image3DMaxDepth,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_IMAGE3D_MAX_HEIGHT,
			sizeof(this->image3DMaxHeight),
            (void*)&this->image3DMaxHeight,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_IMAGE3D_MAX_WIDTH,
			sizeof(this->image3DMaxWidth),
            (void*)&this->image3DMaxWidth,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_LOCAL_MEM_SIZE,
			sizeof(this->localMemSize),
            (void*)&this->localMemSize,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_LOCAL_MEM_TYPE,
			sizeof(this->localMemType),
            (void*)&this->localMemType,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_CLOCK_FREQUENCY,
			sizeof(this->maxClockFrequency),
            (void*)&this->maxClockFrequency,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_COMPUTE_UNITS,
			sizeof(this->maxComputeUnits),
            (void*)&this->maxComputeUnits,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_CONSTANT_ARGS,
			sizeof(this->maxConstantArgs),
            (void*)&this->maxConstantArgs,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
			sizeof(this->maxConstantBufferSize),
            (void*)&this->maxConstantBufferSize,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_MEM_ALLOC_SIZE,
			sizeof(this->maxMemAllocSize),
            (void*)&this->maxMemAllocSize,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_PARAMETER_SIZE,
			sizeof(this->maxParameterSize),
            (void*)&this->maxParameterSize,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_READ_IMAGE_ARGS,
			sizeof(this->maxReadImageArgs),
            (void*)&this->maxReadImageArgs,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_SAMPLERS,
			sizeof(this->maxSamplers),
            (void*)&this->maxSamplers,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_WORK_GROUP_SIZE,
			sizeof(this->maxWorkGroupSize),
            (void*)&this->maxWorkGroupSize,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
			sizeof(this->maxWorkItemDimensions),
            (void*)&this->maxWorkItemDimensions,
            0);

	// Now that the work dimensions are known, allocate memory for the work item sizes
	maxWorkItemSizes = new size_t[maxWorkItemDimensions];
	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_WORK_ITEM_SIZES,
			sizeof(this->maxWorkItemSizes) * maxWorkItemDimensions,
            (void*)&this->maxWorkItemSizes,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
			sizeof(this->maxWriteImageArgs),
            (void*)&this->maxWriteImageArgs,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MEM_BASE_ADDR_ALIGN,
			sizeof(this->memBaseAddrAlign),
            (void*)&this->memBaseAddrAlign,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,
			sizeof(this->minDataTypeAlignSize),
            (void*)&this->minDataTypeAlignSize,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_NAME,
            sizeof(this->name),
            (void*)this->name,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_PLATFORM,
            sizeof(this->platform),
            (void*)this->platform,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,
			sizeof(this->preferredVectorWidth_Char),
            (void*)&this->preferredVectorWidth_Char,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,
			sizeof(this->preferredVectorWidth_Short),
            (void*)&this->preferredVectorWidth_Short,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,
			sizeof(this->preferredVectorWidth_Int),
            (void*)&this->preferredVectorWidth_Int,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,
			sizeof(this->preferredVectorWidth_Long),
            (void*)&this->preferredVectorWidth_Long,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,
			sizeof(this->preferredVectorWidth_Float),
            (void*)&this->preferredVectorWidth_Float,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
			sizeof(this->preferredVectorWidth_Double),
            (void*)&this->preferredVectorWidth_Double,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_PROFILE,
			sizeof(this->deviceProfile),
            (void*)this->deviceProfile,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_PROFILING_TIMER_RESOLUTION,
			sizeof(this->profilingTimerResolution),
            (void*)&this->profilingTimerResolution,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_QUEUE_PROPERTIES,
			sizeof(this->queueProperties),
            (void*)&this->queueProperties,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_SINGLE_FP_CONFIG,
			sizeof(this->singleFpConfig),
            (void*)&this->singleFpConfig,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DEVICE_TYPE,
			sizeof(this->type),
            (void*)&this->type,
            0);

	 clGetDeviceInfo(this->deviceID,
            CL_DEVICE_VENDOR,
            sizeof(this->vendor),
            (void*)this->vendor,
            0);
            
    clGetDeviceInfo(this->deviceID,
            CL_DEVICE_VENDOR_ID,
            sizeof(this->vendorID),
            (void*)&this->vendorID,
            0);
          
    clGetDeviceInfo(this->deviceID,
            CL_DEVICE_VERSION,
            sizeof(this->deviceVersion),
            (void*)this->deviceVersion,
            0);

	clGetDeviceInfo(this->deviceID,
            CL_DRIVER_VERSION,
            sizeof(this->driverVersion),
            (void*)this->driverVersion,
            0);

}


ClManager::clPlatformProp::clPlatformProp()
{
    nrDevices = 0;
    devices = 0;
}

ClManager::clPlatformProp::~clPlatformProp()
{
    if(nrDevices) delete[] devices;
}

void ClManager::ListAllDevices(std::ostream& out)
{
    for(size_t i = 0; i < nrPlatforms; i++)
    {
		clPlatformProp* current = &platforms[i];
        out<<" Platform: "<<current->name<<std::endl;
		out<<"  Version: "<<current->version<<std::endl;
		out<<"  Vendor: "<<current->vendor<<std::endl;
        for(size_t j = 0; j < current->nrDevices; j++)
        {
			clDeviceProp* dev = &current->devices[j];
            out<<"   Device: "<<dev->name<<std::endl;
			out<<"    Global memory: "<<dev->globalMemSize/1024/1024<<" MB"<<std::endl;
			out<<"    Compute units (cores): "<<dev->maxComputeUnits<<std::endl;
			out<<"    Single-precision SIMD width: "<<dev->preferredVectorWidth_Float<<std::endl;
			out<<"    Double-precision SIMD width: "<<dev->preferredVectorWidth_Double<<std::endl;
        }
        out<<std::endl;
    }
}