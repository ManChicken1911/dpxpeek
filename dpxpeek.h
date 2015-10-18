typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef float SINGLE;
typedef unsigned char BYTE;

typedef struct _GenericFileHeader
{
	DWORD Magic;            /* Magic number */
	DWORD ImageOffset;      /* Offset to start of image data in bytes */
	char  Version[8];       /* Version stamp of header format */
	DWORD FileSize;         /* Total DPX file size in bytes */
	DWORD DittoKey;         /* Image content specifier */
	DWORD GenericSize;      /* Generic section header length in bytes */
	DWORD IndustrySize;     /* Industry-specific header length in bytes */
	DWORD UserSize;         /* User-defined data length in bytes */
	char  FileName[100];    /* Name of DPX file */
	char  TimeDate[24];     /* Time and date of file creation */
	char  Creator[100];     /* Name of file creator */
	char  Project[200];     /* Name of project */
	char  Copyright[200];   /* File contents copyright information */
	DWORD EncryptKey;       /* Encryption key */
	char  Reserved[104];    /* Reserved field used for padding */
} GENERICFILEHEADER;


typedef struct _GenericImageHeader
{
	WORD  Orientation;            /* Image orientation */
	WORD  NumberElements;         /* Number of image elements */
	DWORD PixelsPerLine;          /* Pixels per line */
	DWORD LinesPerElement;        /* Lines per image element */
	struct _ImageElement
	{
		DWORD  DataSign;          /* Data sign extension */
		DWORD  LowData;           /* Reference low data code value */
		SINGLE LowQuantity;       /* Reference low quantity represented */
		DWORD  HighData;          /* Reference high data code value */
		SINGLE HighQuantity;      /* Reference high quantity represented */
		BYTE   Descriptor;        /* Descriptor for image element */
		BYTE   Transfer;          /* Transfer characteristics for element */
		BYTE   Colorimetric;      /* Colormetric specification for element */
		BYTE   BitSize;           /* Bit size for element */
		WORD   Packing;           /* Packing for element */
		WORD   Encoding;          /* Encoding for element */
		DWORD  DataOffset;        /* Offset to data of element */
		DWORD  EndOfLinePadding;  /* End of line padding used in element */
		DWORD  EndOfImagePadding; /* End of image padding used in element */
		char   Description[32];   /* Description of element */
	} ImageElement[8];
	BYTE Reserved[52];            /* Reserved field used for padding */
} GENERICIMAGEHEADER;


typedef struct _GenericOrientationHeader
{
	DWORD  XOffset;             /* X offset */
	DWORD  YOffset;             /* Y offset */
	SINGLE XCenter;             /* X center */
	SINGLE YCenter;             /* Y center */
	DWORD  XOriginalSize;       /* X original size */
	DWORD  YOriginalSize;       /* Y original size */
	char   FileName[100];       /* Source image file name */
	char   TimeDate[24];        /* Source image date and time */
	char   InputName[32];       /* Input device name */
	char   InputSN[32];         /* Input device serial number */
	WORD   Border[4];           /* Border validity (XL, XR, YT, YB) */
	DWORD  AspectRatio[2];      /* Pixel aspect ratio (H:V) */
	BYTE   Reserved[28];        /* Reserved field used for padding */
} GENERICORIENTATIONHEADER;


typedef struct _IndustryFilmInfoHeader
{
	char   FilmMfgId[2];      /* Film manufacturer ID code */
	char   FilmType[2];       /* File type */
	char   Offset[2];         /* Offset in perfs */
	char   Prefix[6];         /* Prefix */
	char   Count[4];          /* Count */
	char   Format[32];        /* Format */
	DWORD  FramePosition;     /* Frame position in sequence */
	DWORD  SequenceLen;       /* Sequence length in frames */
	DWORD  HeldCount;         /* Held count */
	SINGLE FrameRate;         /* Frame rate of original in frames/sec */
	SINGLE ShutterAngle;      /* Shutter angle of camera in degrees */
	char   FrameId[32];       /* Frame identification */
	char   SlateInfo[100];    /* Slate information */
	BYTE   Reserved[56];      /* Reserved field used for padding */
} INDUSTRYFILMINFOHEADER;


typedef struct _IndustryTelevisionInfoHeader
{
	DWORD  TimeCode;            /* SMPTE time code */
	DWORD  UserBits;            /* SMPTE user bits */
	BYTE   Interlace;           /* Interlace */
	BYTE   FieldNumber;         /* Field number */
	BYTE   VideoSignal;         /* Video signal standard */
	BYTE   Padding;             /* Structure alignment padding */
	SINGLE HorzSampleRate;      /* Horizontal sampling rate in Hz */
	SINGLE VertSampleRate;      /* Vertical sampling rate in Hz */
	SINGLE FrameRate;           /* Temporal sampling rate or frame rate
								   in Hz */
	SINGLE TimeOffset;          /* Time offset from sync to first pixel */
	SINGLE Gamma;               /* Gamma value */
	SINGLE BlackLevel;          /* Black level code value */
	SINGLE BlackGain;           /* Black gain */
	SINGLE Breakpoint;          /* Breakpoint */
	SINGLE WhiteLevel;          /* Reference white level code value */
	SINGLE IntegrationTimes;    /* Integration time(s) */
	BYTE   Reserved[76];        /* Reserved field used for padding */
} INDUSTRYTELEVISIONINFOHEADER;
