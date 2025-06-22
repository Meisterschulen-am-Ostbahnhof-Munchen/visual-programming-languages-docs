# APPEND_STRING_2

![APPEND_STRING_2](https://github.com/user-attachments/assets/a7a1cd64-fe08-4c13-8cff-495263d507ca)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `APPEND_STRING_2` dient dazu, zwei beliebige Datentypen in Strings umzuwandeln und diese zu einem einzigen String zu verketten. Der Block ist besonders nützlich, wenn verschiedene Datentypen in einer einheitlichen String-Repräsentation kombiniert werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Verarbeitung. Bei diesem Ereignis werden die Eingangsdaten `IN_1` und `IN_2` gelesen und verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Verarbeitung und liefert das Ergebnis als String über die Variable `OUT`.

### **Daten-Eingänge**
- **IN_1**: Erster Eingangswert beliebigen Typs, der in einen String umgewandelt wird.
- **IN_2**: Zweiter Eingangswert beliebigen Typs, der in einen String umgewandelt wird.

### **Daten-Ausgänge**
- **OUT**: Der resultierende String, der durch die Verkettung der umgewandelten Werte von `IN_1` und `IN_2` entsteht.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
1. Bei Eintreffen des Ereignisses `REQ` werden die Werte der Eingänge `IN_1` und `IN_2` in Strings umgewandelt.
2. Diese Strings werden anschließend verkettet.
3. Das Ergebnis wird über den Ausgang `OUT` ausgegeben und das Ereignis `CNF` wird ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock unterstützt beliebige Datentypen für die Eingänge `IN_1` und `IN_2`, da diese automatisch in Strings konvertiert werden.
- Die Verkettung erfolgt in der Reihenfolge `IN_1` + `IN_2`.

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Processing**: Verarbeitet die Eingangsdaten und erzeugt den Ausgabestring.
3. **Done**: Sendet das Ereignis `CNF` mit dem Ergebnis.

## Anwendungsszenarien
- Erstellung von Log-Meldungen aus verschiedenen Datentypen.
- Generierung von dynamischen Texten in Benutzeroberflächen.
- Kombination von Sensorwerten und Statusmeldungen für Diagnosezwecke.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen String-Verkettungsblöcken bietet `APPEND_STRING_2` die Flexibilität, beliebige Datentypen zu verarbeiten.
- Andere Blöcke erfordern oft bereits String-Eingänge oder unterstützen nur eine begrenzte Anzahl von Datentypen.

## Fazit
Der `APPEND_STRING_2` Funktionsblock ist ein vielseitiges Werkzeug zur String-Manipulation, das durch seine Unterstützung beliebiger Datentypen besonders flexibel einsetzbar ist. Ideal für Anwendungen, bei denen verschiedene Datenquellen in einer einheitlichen Textform zusammengeführt werden müssen.
