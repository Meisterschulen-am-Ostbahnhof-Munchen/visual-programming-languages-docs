# ATimeOut

![ATimeOut](https://user-images.githubusercontent.com/116869307/214142228-09857ba5-6164-4597-bb66-8a99e74f4d14.png)

* * * * * * * * * *  

## Einleitung  
Die IEC 61499 ist ein internationaler Standard für die Modellierung verteilter industrieller Steuerungssysteme. Der **ATimeOut**-Baustein (Active Timeout) ist ein Funktionsbaustein, der einen aktiven Timeout-Mechanismus bereitstellt. Dieser Aufsatz beschreibt die Struktur, das Verhalten und die typischen Anwendungen des ATimeOut-Bausteins.  

## Struktur des ATimeOut-Bausteins  
Der ATimeOut-Baustein ist als **Basic Function Block (BFB)** oder **Composite Function Block (CFB)** in der IEC 61499 spezifiziert.  

### Schnittstelle (Interface)  
Die typische Schnittstelle des ATimeOut-Bausteins umfasst:  

- **Eingangsereignisse (Event Inputs)**:  
  - **START**: Löst den Timeout mit der konfigurierten Dauer aus.  
  - **STOP**: Bricht den laufenden Timeout ab.  
  - **RESET**: Setzt den Timeout zurück.  

- **Ausgangsereignisse (Event Outputs)**:  
  - **TimeOut**: Wird ausgelöst, wenn der Timeout abgelaufen ist.  

- **Eingangsvariablen (Input Variables)**:  
  - **PT (Preset Time)**: Die vordefinierte Timeout-Dauer (TIME-Datentyp).  

- **Ausgangsvariablen (Output Variables)**:  
  - **Q**: Boolescher Ausgang, der den aktiven Timeout-Zustand anzeigt (TRUE = Timeout läuft).  

## Verhalten des ATimeOut-Bausteins  
1. **Start des Timeouts**:  
   - Bei Empfang des **START**-Ereignisses beginnt der Timeout mit der in **PT** definierten Dauer.  
   - Der Ausgang **Q** wird auf TRUE gesetzt.  

2. **Abbruch des Timeouts**:  
   - Ein **STOP**-Ereignis setzt **Q** auf FALSE und hält den Timeout an.  

3. **Timeout-Ablauf**:  
   - Nach Ablauf von **PT** wird das **TimeOut**-Ereignis ausgelöst und **Q** auf FALSE gesetzt.  

4. **Reset**:  
   - Das **RESET**-Ereignis setzt den internen Timer zurück.  

## Technische Besonderheiten  
- Der Baustein kann sowohl in zyklischen als auch ereignisgesteuerten Systemen eingesetzt werden.  
- Die Timeout-Logik ist unabhängig von der Zykluszeit des übergeordneten Systems.  

## Anwendungsbeispiele  
- **Überwachung von Kommunikationszeitüberschreitungen** in verteilten Steuerungssystemen  
- **Maschinensicherheit**: Erkennung von Stillstandszeiten oder fehlenden Sensorupdates  
- **Prozesssteuerung**: Timeout für kritische Operationen  

## Vergleich mit ähnlichen Bausteinen  
| Feature        | ATimeOut | ARTimeOut (Adapter) | E_PULSE |  
|----------------|----------|---------------------|---------|  
| Timeout-Trigger| START    | START               | REQ     |  
| Abbruch        | STOP     | STOP                | R (Reset)|  
| Rückmeldung    | TimeOut  | TimeOut             | CNF     |  
| Typ           | FB       | Adapter             | FB      |  

## Fazit  
Der ATimeOut-Baustein bietet eine robuste Lösung für Timeout-Mechanismen in IEC 61499-Systemen. Durch seine klare Schnittstelle und flexible Einsatzmöglichkeiten eignet er sich besonders für Sicherheits- und Überwachungsfunktionen in industriellen Steuerungen. Die Unabhängigkeit von der Zykluszeit macht ihn zudem für ereignisgesteuerte Architekturen interessant.