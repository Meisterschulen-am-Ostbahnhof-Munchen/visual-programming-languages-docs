# BOOL2BOOL

<img width="1171" height="181" alt="BOOL2BOOL" src="https://github.com/user-attachments/assets/6bd3aad6-d3d2-4f97-a177-56ad21b2099a" />

* * * * * * * * * *
## Einleitung
Der BOOL2BOOL Funktionsblock ist ein einfacher Konverter, der einen booleschen Eingangswert auf einen booleschen Ausgangswert abbildet. Er dient als grundlegender Baustein für die Signalverarbeitung in 4diac-IDE Anwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung (triggert die Konvertierung)

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung (wird nach erfolgreicher Konvertierung ausgelöst)

### **Daten-Eingänge**
- **IN**: Boolescher Eingangswert (BOOL)

### **Daten-Ausgänge**
- **OUT**: Boolescher Ausgangswert (BOOL)

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Empfang eines REQ-Ereignisses kopiert der Funktionsblock den Wert des IN-Eingangs direkt auf den OUT-Ausgang und löst das CNF-Ereignis aus. Die Implementierung erfolgt durch einen einfachen ST-Algorithmus:
```ST
ALGORITHM REQ
OUT := IN;
END_ALGORITHM
```

## Technische Besonderheiten
- Einfachster möglicher Konverter für boolesche Werte
- Keine Zustandsbehaftung (stateless)
- Sofortige Ausführung ohne Verzögerung

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Er verhält sich rein funktional.

## Anwendungsszenarien
- Signalweiterleitung in logischen Schaltungen
- Anpassung von Signalpegeln zwischen Komponenten
- Debugging und Protokollierung von booleschen Signalen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu komplexeren Konvertern (wie z.B. INT2BOOL) bietet BOOL2BOOL:
- Keine Datentypkonvertierung
- Minimaler Ressourcenverbrauch
- Höchste Ausführungsgeschwindigkeit

## Fazit
Der BOOL2BOOL Funktionsblock ist ein essentieller Grundbaustein für die boolesche Signalverarbeitung in 4diac-IDE. Seine Einfachheit macht ihn besonders robust und performant, während er gleichzeitig alle grundlegenden Anforderungen an eine boolesche Signalweiterleitung erfüllt.
