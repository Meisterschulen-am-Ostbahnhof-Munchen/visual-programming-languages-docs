# WORD2WORD

<img width="1173" height="182" alt="WORD2WORD" src="https://github.com/user-attachments/assets/6982d15b-e332-4c06-94b0-f5fd99991fe6" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock WORD2WORD dient zur direkten Übertragung eines WORD-Wertes vom Eingang zum Ausgang. Es handelt sich um einen einfachen Konvertierungsbaustein ohne Datenmanipulation.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung (triggert die Datenübertragung)
  - Verbundener Dateneingang: IN (WORD)

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung (wird nach erfolgreicher Übertragung ausgelöst)
  - Verbundener Datenausgang: OUT (WORD)

### **Daten-Eingänge**
- **IN**: WORD-Eingangswert (zu übertragender Wert)

### **Daten-Ausgänge**
- **OUT**: WORD-Ausgangswert (übertragener Wert)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Empfang eines REQ-Ereignisses wird der aktuelle Wert am IN-Eingang unverändert an den OUT-Ausgang kopiert. Anschließend wird ein CNF-Ereignis ausgelöst.

Der Algorithmus ist in ST (Structured Text) implementiert:
```ST
ALGORITHM REQ
OUT := IN;
END_ALGORITHM
```

## Technische Besonderheiten
- Einfache 1:1-Wertübertragung ohne Konvertierung oder Skalierung
- Keine Pufferung der Daten zwischen REQ und CNF
- Sofortige Ausführung bei REQ-Eingang

## Zustandsübersicht
Der FB besitzt keine internen Zustände. Jede REQ-Anforderung wird unabhängig verarbeitet.

## Anwendungsszenarien
- Weiterleitung von WORD-Werten in Funktionsblockketten
- Signalübertragung ohne Veränderung
- Als Platzhalter oder Verbindungselement in komplexeren FB-Netzwerken

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu Konvertierungsbausteinen (z.B. WORD_TO_INT) findet keine Datentypumwandlung statt
- Einfacher als Bausteine mit zusätzlicher Funktionalität (z.B. Filter, Verzögerungen)
- Ähnlich zu anderen 1:1-Übertragungsbausteinen, aber spezifisch für WORD-Datentyp

## Fazit
WORD2WORD ist ein grundlegender Funktionsblock für die unveränderte Weitergabe von WORD-Werten in IEC 61499-Systemen. Seine Einfachheit macht ihn zu einem nützlichen Baustein für Basisverbindungen, während die spezifische Typbindung Typsicherheit gewährleistet.
