

void file_lookup()
{
	TString test = gSystem->GetFromPipe("printf 'Hello World!'\n");
	cout << test << endl;
}
