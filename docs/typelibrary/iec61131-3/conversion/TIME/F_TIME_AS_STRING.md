# F_TIME_AS_STRING

<img width="1464" height="212" alt="F_TIME_AS_STRING" src="https://github.com/user-attachments/assets/e9156094-840f-4d48-bc5d-8fd718a9e157" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_TIME_AS_STRING` dient zur Konvertierung eines `TIME`-Wertes in einen `STRING`-Wert. Er ist besonders nützlich, wenn Zeitwerte für die Anzeige oder Protokollierung in einer textuellen Form benötigt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Löst die Ausführung des Funktionsblocks aus. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Ausführung des Funktionsblocks. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`TIME`): Der Zeitwert, der in einen String konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`STRING`): Der resultierende String, der den konvertierten Zeitwert repräsentiert.

### **Adapter**
Es sind keine Adapter für diesen Funktionsblock definiert.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Dabei wird der `TIME`-Wert am Eingang `IN` in einen `STRING`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Die Konvertierung erfolgt mithilfe der Funktion `TIME_AS_STRING`. Nach Abschluss der Konvertierung wird das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (SimpleFB) und führt keine komplexen Zustandsübergänge durch.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge. Der Block führt die Konvertierung bei jedem `REQ`-Ereignis durch und signalisiert die Fertigstellung mit `CNF`.

## Anwendungsszenarien
- Anzeige von Zeitwerten in Benutzeroberflächen.
- Protokollierung von Zeitstempeln in textuellen Logdateien.
- Integration in Systeme, die Zeitwerte als Strings verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_INT_AS_STRING` oder `F_REAL_AS_STRING` ist dieser Block speziell für die Konvertierung von `TIME`-Werten optimiert.
- Ähnliche Funktionalität könnte auch mit einem benutzerdefinierten Algorithmus erreicht werden, dieser Block bietet jedoch eine standardisierte und wiederverwendbare Lösung.

## Fazit
Der `F_TIME_AS_STRING`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeitwerte in Strings umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einem nützlichen Baustein für verschiedene Anwendungen, bei denen Zeitwerte in textueller Form benötigt werden.
