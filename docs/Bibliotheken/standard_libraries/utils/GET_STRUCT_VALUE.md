# GET_STRUCT_VALUE

![GET_STRUCT_VALUE](https://github.com/user-attachments/assets/ba148684-567d-4115-9405-c518fb73644a)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `GET_STRUCT_VALUE` dient dazu, einen bestimmten Wert aus einer Struktur auszulesen. Er ermöglicht den Zugriff auf einzelne Mitglieder einer Struktur, einschließlich verschachtelter Mitglieder, die über den Punktoperator (.) angesprochen werden können.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet den Lesevorgang. Wird mit den Daten-Eingängen `member` und `in_struct` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss des Lesevorgangs. Wird mit den Daten-Ausgängen `QO` und `output` verknüpft.

### **Daten-Eingänge**
- **in_struct**: Die Struktur, aus der ein Wert ausgelesen werden soll. Der Datentyp ist `ANY`, was bedeutet, dass verschiedene Strukturtypen unterstützt werden.
- **member**: Der Name des Strukturmitglieds, das ausgelesen werden soll. Bei verschachtelten Mitgliedern wird der Punktoperator (.) verwendet. Der Datentyp ist `STRING`.

### **Daten-Ausgänge**
- **QO**: Ein boolescher Wert (`BOOL`), der anzeigt, ob der Lesevorgang erfolgreich war (`TRUE`) oder nicht (`FALSE`).
- **output**: Der ausgelesene Wert des angegebenen Strukturmitglieds. Der Datentyp ist `ANY`, was bedeutet, dass der Wert je nach Strukturmitglied unterschiedlich sein kann. Bleibt unverändert, wenn `QO` `FALSE` ist.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
1. Der Funktionsblock wird durch das Ereignis `REQ` aktiviert.
2. Er liest den Wert des in `member` angegebenen Strukturmitglieds aus der in `in_struct` übergebenen Struktur.
3. Bei erfolgreichem Auslesen wird `QO` auf `TRUE` gesetzt und der Wert in `output` ausgegeben.
4. Bei einem Fehler (z.B. wenn das Mitglied nicht existiert) wird `QO` auf `FALSE` gesetzt und `output` bleibt unverändert.
5. Das Ereignis `CNF` signalisiert den Abschluss des Vorgangs.

## Technische Besonderheiten
- Unterstützt den Zugriff auf verschachtelte Strukturmitglieder über den Punktoperator (.).
- Der Datentyp `ANY` für `in_struct` und `output` ermöglicht die Verwendung mit verschiedenen Strukturtypen.
- Der Fehlerfall wird durch `QO` klar signalisiert.

## Zustandsübersicht
- **Idle**: Wartet auf das `REQ`-Ereignis.
- **Processing**: Liest den Wert aus der Struktur.
- **Completed**: Sendet das `CNF`-Ereignis mit dem Ergebnis.

## Anwendungsszenarien
- Auslesen von Werten aus komplexen Strukturen in Steuerungsanwendungen.
- Zugriff auf verschachtelte Daten in Konfigurationsstrukturen.
- Fehlerbehandlung bei ungültigen Strukturzugriffen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Leseoperationen bietet `GET_STRUCT_VALUE` die Flexibilität, auf beliebige Strukturmitglieder zuzugreifen.
- Andere Bausteine könnten auf bestimmte Strukturtypen spezialisiert sein, während `GET_STRUCT_VALUE` generisch ist.

## Fazit
Der `GET_STRUCT_VALUE`-Funktionsblock ist ein vielseitiges Werkzeug für den Zugriff auf Strukturwerte in 4diac-IDE-Anwendungen. Seine Unterstützung für verschachtelte Mitglieder und generische Datentypen macht ihn besonders nützlich in komplexen Szenarien. Die klare Fehlerrückmeldung durch `QO` erleichtert die robuste Programmierung.
