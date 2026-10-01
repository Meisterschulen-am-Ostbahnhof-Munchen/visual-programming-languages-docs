/**
 * Fuegt einem VORHANDENEN Google Form einen neuen Abschnitt "Datentypen" mit
 * 10 Fragen hinzu (Quelle: docs/de/Allgemeines/Datentypen/index.md,
 * IEC 61131-3 / IEC 61499). Es wird kein neues Formular erstellt.
 *
 * Verwendung (Variante A, empfohlen): im Formular -> Drei-Punkte-Menue ->
 *   "Skript-Editor" oeffnen, Code einfuegen, "addDatentypenSection" ausfuehren.
 * Variante B: eigenständiges Skript, FORM_ID unten eintragen
 *   (Teil der Formular-URL zwischen /d/ und /edit).
 */
var FORM_ID = ''; // nur fuer Variante B noetig
var SECTION_TITLE = 'Datentypen (IEC 61131-3 / IEC 61499)';

function addDatentypenSection() {
  var form = FORM_ID ? FormApp.openById(FORM_ID) : FormApp.getActiveForm();
  if (!form) throw new Error('Kein Formular gefunden: FORM_ID eintragen oder Skript aus dem Formular heraus oeffnen.');
  if (!form.isQuiz()) form.setIsQuiz(true); // noetig fuer Punkte/Feedback

  form.addPageBreakItem()
    .setTitle(SECTION_TITLE)
    .setHelpText('10 Fragen zu den elementaren Datentypen gemäß DIN EN 61131-3 und IEC 61499.');

  // Jede Frage: [Text, [Antworten], Index der richtigen Antwort, Erklärung]
  var questions = [
    ['Welche Typen gehören zu den Bit-Datentypen nach IEC 61131-3?',
      ['BOOL, BYTE, WORD, DWORD, LWORD', 'SINT, INT, DINT, LINT', 'REAL, LREAL', 'STRING, WSTRING'], 0,
      'Bit-Datentypen: BOOL, BYTE, WORD, DWORD, LWORD. SINT..LINT sind Ganzzahlen mit Vorzeichen.'],

    ['Welche Datentypen zählen zu den Gleitpunktzahlen?',
      ['SINT und INT', 'REAL und LREAL', 'TIME und DATE', 'BYTE und WORD'], 1,
      'Gleitpunktzahlen: REAL (32 Bit) und LREAL (64 Bit).'],

    ['Welche Typen gehören zur Gruppe „Zeit und Datum"?',
      ['STRING, WSTRING, BYTE, WORD', 'BOOL, SINT, INT, DINT', 'TIME, DATE, TOD, DT', 'REAL, LREAL, LINT, ULINT'], 2,
      'Zeit und Datum: TIME, DATE, TOD (TIME_OF_DAY) und DT (DATE_AND_TIME).'],

    ['Welche Datentypen sind Zeichenfolgen?',
      ['CHAR und WCHAR', 'STRING und WSTRING', 'BYTE und WORD', 'TIME und DT'], 1,
      'Zeichenfolgen: STRING und WSTRING.'],

    ['Welchen Wertebereich hat SINT (8 Bit, mit Vorzeichen)?',
      ['0 bis 255', '−32.768 bis 32.767', '−128 bis 127', '−256 bis 255'], 2,
      'SINT: −128 … 127. USINT (vorzeichenlos) geht von 0 bis 255.'],

    ['Was ist der größte Wert von UINT (16 Bit, vorzeichenlos)?',
      ['255', '32.767', '65.535', '4.294.967.295'], 2,
      'UINT: 0 … 65.535. 4.294.967.295 ist der Maximalwert von UDINT bzw. DWORD.'],

    ['Wie viele Bit hat der Datentyp LINT?',
      ['16 Bit', '32 Bit', '64 Bit', '128 Bit'], 2,
      'LINT ist eine lange Ganzzahl mit 64 Bit (8 Byte).'],

    ['Welches Kürzel hat der Datentyp UDINT?',
      ['UD', 'UDI', 'DI', 'UL'], 1,
      'UDINT = UDI, DINT = DI, ULINT = ULI.'],

    ['Was gilt für den Datentyp QUARTER?',
      ['2 Bit, in der Norm festgelegt', '4 Bit, in der Norm festgelegt', '2 Bit, nicht normativ festgelegt', '8 Bit, nicht normativ festgelegt'], 2,
      'QUARTER hat 2 Bit (Wert 0 bis 3) und ist nicht normativ festgelegt.'],

    ['Welcher Adapter gehört zum Datentyp LREAL?',
      ['AR', 'ALR', 'AL', 'ALI'], 1,
      'LREAL → ALR, REAL → AR, LWORD → AL, LINT → ALI.']
  ];

  questions.forEach(function (q) {
    var item = form.addMultipleChoiceItem();
    item.setTitle(q[0]);
    item.setRequired(true);
    item.setPoints(1);
    item.setChoices(q[1].map(function (text, i) {
      return item.createChoice(text, i === q[2]);
    }));
    item.setFeedbackForCorrect(FormApp.createFeedback().setText('Richtig! ' + q[3]).build());
    item.setFeedbackForIncorrect(FormApp.createFeedback().setText('Leider falsch. ' + q[3]).build());
  });

  Logger.log('Abschnitt hinzugefügt: ' + form.getEditUrl());
}
