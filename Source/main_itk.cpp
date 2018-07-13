
#include "itkOpenThinning.h"

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

static const char DEFAULT_LOOKUP_TABLE_FILENAME[] = "../../Data/LookupTables/Thinning_Simple.bin";

int main(int argc, char** argv)
{
	using input_type = itk::Image<float, 3>;
	using output_type = itk::Image<unsigned char, 3>;

	if (argc == 4)
	{
		LookupTable lookuptable;
		if (!lookuptable.readFile(argv[1]))
		{
			return EXIT_FAILURE;
		}

		auto reader = itk::ImageFileReader<input_type>::New();
		reader->SetFileName(argv[2]);

		auto thinning_filter = itk::OpenThinning<input_type, output_type>::New();
		thinning_filter->SetInput(reader->GetOutput());
		thinning_filter->SetLookupTable(lookuptable);

		auto writer = itk::ImageFileWriter<output_type>::New();
		writer->SetFileName(argv[3]);
		writer->SetInput(thinning_filter->GetOutput());
		writer->Update();
	}
	else // create example data to show how filter runs
	{
		// Print the intended usage of this program
		std::cout << "Usage: " << argv[0] << " <Lookup Table Filename> <Input Volume Filename> <Output Volume Filename>\n\n";

		// -- Read the default lookup table --

		std::cout << "Reading default lookup table \"" << DEFAULT_LOOKUP_TABLE_FILENAME << "\"\n";

		LookupTable lookuptable;
		if (!lookuptable.readFile(DEFAULT_LOOKUP_TABLE_FILENAME))
		{
			return EXIT_FAILURE;
		}

		input_type::IndexType start;// = { 0, 0, 0 };
		input_type::SizeType size;// = { 50, 70, 45 };

		auto input = input_type::New();
		input->SetRegions(input_type::RegionType(start, size));
		input->Allocate();
		input->FillBuffer(0.f);

		input_type::IndexType start2;// = { 10, 10, 10 };
		input_type::SizeType size2;// = { 5, 50, 5 };

		itk::ImageRegionIterator<input_type> it(input, input_type::RegionType(start2, size2));
		for (it.GoToBegin(); !it.IsAtEnd(); ++it)
		{
			it.Set(1.f);
		}

		auto thinning_filter = itk::OpenThinning<input_type, output_type>::New();
		thinning_filter->SetInput(input);
		thinning_filter->SetLookupTable(lookuptable);
		thinning_filter->Update();
	}

	return EXIT_SUCCESS;
}
