
import re


class LineCredential():
    def getCredential(credentialFile="linecredential.txt"):
        """		
        Get credential from 'linecredential.txt'
        Credential File Format:
            channel_access_token:channel_secret
            ex:
                xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx:yyyyyyyyyyyyyyyyyyyyyyyyyyy

        :param credentialFile: Credential file
        :type credentialFile: string
        :return: first line of Credential 
        :rtype: string
        :raises: NameError if credential file not found
        """

        try:
            credentialFile = open(credentialFile, 'r')
            credentialFile.seek(0)
            credentialLine = credentialFile.read().splitlines()
            credentialFile.close()
            #print credentialLine
            return credentialLine[0]    # return only first line

        except IOError:
            print(
                f"\n* File {credentialFile} does not exist! Please check and try again!\n")
            raise NameError(f"{credentialFile} not found!!")

    def extractCredential(credentialLine):
        try:
            x = re.findall(r"(.+):(.+)", credentialLine)
            #print(x)
            return x[0]
        except IndexError:
            print(f"Error extractCredential: {credentialLine}")
            assert False

#credentialLine = LineCredential.getCredential()
#channel_access_token, channel_secret = LineCredential.extractCredential(credentialLine)