### E\_DELAY

Verzögerte Ausbreitung eines Ereignisses - abbrechbar

![](https://user-images.githubusercontent.com/113907528/227959784-5391cacc-ca41-4bca-865e-7393a908e252.png)

EVENT\_INPUT

<table><tbody><tr><td>START</td><td>Verzögerung beginnen</td></tr><tr><td>STOP</td><td>Verzögerung abbrechen</td></tr></tbody></table>

EVENT\_OUTPUT

<table><tbody><tr><td>EO</td><td>Verzögertes Ereignis</td></tr></tbody></table>

VAR\_INPUT

<table><tbody><tr><td>DT : TIME</td><td>Verzögerungszeit</td></tr></tbody></table>

Nach dem Auftreten eines Ereignisses am **Eingang START** und dem **Zeitintervall Zeit DT** wird ein **Ereignis an EO** erzeugt. Die Ereignisverzögerung wird durch ein Auftreten eines Ereignisses am **Eingang STOP** widerrufen. Wenn mehrere Ereignisse am **Eingang START** vor dem Auftreten eines **Ereignisses an EO** auftreten, tritt nach dem ersten Ereignisauftritt am **Eingang START** und dem anschließenden **Verstreichen von DT** nur ein einzelnes **Ereignis an EO** auf. Es wird keine Zeitverzögerung initiiert werden, wenn ein Ereignis am **START-Eingang** mit dem **Wert von DT** auftritt, **der nicht größer als T # 0s.**
